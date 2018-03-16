#include <iostream>
#include "REPLACEME_PROJECT_NAMESPACE/SomeClass.h"
#include "REPLACEME_PROJECT_NAMESPACE/version.h"
#include <websocketpp/server.hpp>
#include <websocketpp/config/asio_no_tls.hpp>

int main( int argc, char* argv[] )
{
	std::cout << "SkeletonCpp program with version " << REPLACEME_PROJECT_NAMESPACE::version::GitDescribe << "\n";
	REPLACEME_PROJECT_NAMESPACE::SomeClass instance;
	std::cout << "SomeClass::someValue returns '" << instance.someValue() << "'\n";

	typedef websocketpp::server<websocketpp::config::asio> server_type;

	try
	{
		int port=443;
		server_type server;
		server.set_http_handler(
			[&server]( websocketpp::connection_hdl hdl )
			{
				std::cout << "HTTP request made\n";
				server.get_con_from_hdl(hdl)->set_body(
					"<!DOCTYPE html>"
					"<html>"
					"<head><title>Foobar strikes again</title>"
					"<script>\n"
						"connection = new WebSocket('ws://' + location.host)\n"
						"connection.onopen = function(evt) {\n"
							"connection.send('Whos there?');\n"
						"};\n"
						"connection.onmessage = function(evt) {\n"
							"document.getElementById('recieved_messages').innerHTML+=evt.data;\n"
						"};\n"
					"</script>"
					"</head>"
					"<body>Welcome to my little test<div id='recieved_messages'></div></body>"
					"</html>"
				);
			} );
		server.set_open_handler(
			[]( websocketpp::connection_hdl hdl )
			{
				std::cout << "Connection open\n";
			} );
		server.set_message_handler(
			[&server]( websocketpp::connection_hdl hdl, server_type::message_ptr msg )
			{
				std::cout << "Got message '" << msg->get_payload() << "'\n";
				server.get_con_from_hdl(hdl)->send( "Echo: "+msg->get_payload() );
			} );
		server.init_asio();
		server.listen( port );
		server.start_accept();
		std::cout << "Starting to listen on port " << port << "\n";
		server.run();
	}
	catch( const std::exception& error )
	{
		std::cerr << "Exception: " << error.what() << "\n";
		return -1;
	}

	return 0;
}
