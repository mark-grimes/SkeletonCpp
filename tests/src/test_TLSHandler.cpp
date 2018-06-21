// Can only use the TLSHandler class if OpenSSL was added as an external to the project
#ifdef ENCRYPTED_WEBSOCKETS_AVAILABLE

#include "REPLACEME_PROJECT_NAMESPACE/detail/TLSHandler.h"
#include "REPLACEME_PROJECT_TESTS_NAMESPACE/testinputs.h"
#include <websocketpp/server.hpp>
#include <websocketpp/client.hpp>
#include <websocketpp/config/asio.hpp>
#include "catch.hpp"

/** @brief WebSocket server that can process the event loop on a different thread, and shut it down on destruction
 * @author Mark Grimes (mark.grimes@rymapt.com)
 * @date 26/Jan/2018 */
class TestServer
{
public:
	typedef websocketpp::server<websocketpp::config::asio_tls> server_type;
	typedef REPLACEME_PROJECT_NAMESPACE::detail::TLSHandler tls_handler_type;

	TestServer() : tlsHandler_( server_.get_alog() )
	{
		server_.set_tls_init_handler( std::bind( &tls_handler_type::handle_tls_init_intermediate, &tlsHandler_, std::placeholders::_1 ) );
		server_.init_asio();
	}
	~TestServer()
	{
		if( server_.is_listening() ) server_.stop_listening();
		// Note that runThread_ won't finish until all of the connections are closed.
		// I don't have a record of them though, so rely on the client(s) to close or this
		// will block indefinitely.
		if( runThread_.joinable() ) runThread_.join();
	}
	template<typename... Ts> void listen( Ts&&... args ) { server_.listen( std::forward<Ts>(args)... ); }
	template<typename... Ts> void start_accept( Ts&&... args ) { server_.start_accept( std::forward<Ts>(args)... ); }
	asio::ip::tcp::endpoint get_local_endpoint( std::error_code& ec ) { return server_.get_local_endpoint(ec); }
	void runOnThread() { runThread_=std::thread( &server_type::run, &server_ ); }
public:
	server_type server_;
	tls_handler_type tlsHandler_;
	std::thread runThread_;
};

SCENARIO( "Test that TLSHandler creates secure connections", "[TLSHandler]" )
{
	GIVEN( "A server and client each connected to different TLSHandlers" )
	{
		typedef websocketpp::client<websocketpp::config::asio_tls> client_type;
		typedef websocketpp::server<websocketpp::config::asio_tls> server_type;
		typedef websocketpp::server<websocketpp::config::asio_tls> connection_type;
		typedef REPLACEME_PROJECT_NAMESPACE::detail::TLSHandler tls_handler_type;

		std::error_code error;
		const std::string sentMessage( "Hello, and welcome to my test" );

		TestServer server;
		server.server_.set_access_channels(websocketpp::log::alevel::none);
		server.server_.set_error_channels(websocketpp::log::elevel::none);
		server.server_.set_open_handler( []( websocketpp::connection_hdl hdl ){ std::cout << "Connection open\n"; } );
		server.server_.set_message_handler( []( websocketpp::connection_hdl hdl, connection_type::message_ptr msg ){ std::cout << "Got message\n"; } );
		server.server_.set_open_handler( [&server,&sentMessage]( websocketpp::connection_hdl hdl )
			{
				server.server_.get_con_from_hdl(hdl)->send( sentMessage );
			} );
		server.tlsHandler_.setCertificateChainFile( REPLACEME_PROJECT_TESTS_NAMESPACE::testinputs::testFileDirectory+"tlscerts/serverA_cert.pem");
		server.tlsHandler_.setPrivateKeyFile( REPLACEME_PROJECT_TESTS_NAMESPACE::testinputs::testFileDirectory+"tlscerts/serverA_key.pem");
		server.listen( 0, error ); { INFO( error.message() ); REQUIRE( !error ); }
		server.start_accept( error ); { INFO( error.message() ); REQUIRE( !error ); }
		server.runOnThread();

		int port=server.get_local_endpoint(error).port();
		{ INFO( error.message() ); REQUIRE( !error ); }

		client_type client;
		tls_handler_type clientTLSHandler( client.get_alog() );
		clientTLSHandler.setVerifyFile( REPLACEME_PROJECT_TESTS_NAMESPACE::testinputs::testFileDirectory+"tlscerts/authorityA_cert.pem");
		client.set_tls_init_handler( std::bind( &tls_handler_type::handle_tls_init_intermediate, &clientTLSHandler, std::placeholders::_1 ) );
		client.set_access_channels(websocketpp::log::alevel::none);
		client.set_error_channels(websocketpp::log::elevel::none);
		client.init_asio();
		std::string receivedMessage;
		client.set_message_handler( [&client,&receivedMessage]( websocketpp::connection_hdl hdl, connection_type::message_ptr msg )
			{
				receivedMessage=msg->get_payload();
				std::error_code error;
				client.get_con_from_hdl(hdl)->close( websocketpp::close::status::normal, "Had enough. Bye.", error );
				if( error ) std::cerr << "Got error '" << error.message() << "' when closing client connection\n";
			} );
		bool clientFailedToConnect=false;
		client.set_fail_handler([&clientFailedToConnect](websocketpp::connection_hdl){ clientFailedToConnect=true; } );
		auto connection=client.get_connection( "wss://localhost:"+std::to_string(port), error );
		{ INFO( error.message() ); REQUIRE( !error ); }
		client.connect( connection );
		client.run();
		REQUIRE_FALSE( clientFailedToConnect );
		CHECK( receivedMessage==sentMessage );
	} // end of '"A server and client each connected to different TLSHandlers"'
} // end of 'SCENARIO "Test that TLSHandler creates secure connections"'

#endif // end of "#ifdef ENCRYPTED_WEBSOCKETS_AVAILABLE"
