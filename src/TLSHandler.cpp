#include "REPLACEME_PROJECT_NAMESPACE/detail/TLSHandler.h"

REPLACEME_PROJECT_NAMESPACE::detail::TLSHandler::TLSHandler( websocketpp::config::asio::alog_type& logger )
	: logger_(logger)
{
	// No operation besides the initialiser list
}

void REPLACEME_PROJECT_NAMESPACE::detail::TLSHandler::setCertificateChainFile( const std::string& filename )
{
	certificateChainFileName_=filename;
}

void REPLACEME_PROJECT_NAMESPACE::detail::TLSHandler::setCertificateChainFile( std::string&& filename )
{
	certificateChainFileName_=std::move(filename);
}

void REPLACEME_PROJECT_NAMESPACE::detail::TLSHandler::setPrivateKeyFile( const std::string& filename )
{
	privateKeyFileName_=filename;
}

void REPLACEME_PROJECT_NAMESPACE::detail::TLSHandler::setPrivateKeyFile( std::string&& filename )
{
	privateKeyFileName_=std::move(filename);
}

void REPLACEME_PROJECT_NAMESPACE::detail::TLSHandler::setVerifyFile( const std::string& filename )
{
	verifyFileName_=filename;
}

void REPLACEME_PROJECT_NAMESPACE::detail::TLSHandler::setVerifyFile( std::string&& filename )
{
	verifyFileName_=std::move(filename);
}

void REPLACEME_PROJECT_NAMESPACE::detail::TLSHandler::setDiffieHellmanParamsFile( const std::string& filename )
{
	diffieHellmanParamsFileName_=filename;
}

void REPLACEME_PROJECT_NAMESPACE::detail::TLSHandler::setDiffieHellmanParamsFile( std::string&& filename )
{
	diffieHellmanParamsFileName_=std::move(filename);
}

void REPLACEME_PROJECT_NAMESPACE::detail::TLSHandler::setCertificateVerificationCallback( std::function<bool(bool,websocketpp::lib::asio::ssl::verify_context&)>&& function )
{
	certificateVerificationCallback_=std::move(function);
}

void REPLACEME_PROJECT_NAMESPACE::detail::TLSHandler::setPasswordCallback( std::function<std::string(size_t,websocketpp::lib::asio::ssl::context::password_purpose)>&& function )
{
	passwordCallback_=std::move(function);
}

websocketpp::lib::shared_ptr<websocketpp::lib::asio::ssl::context> REPLACEME_PROJECT_NAMESPACE::detail::TLSHandler::handle_tls_init_intermediate( websocketpp::connection_hdl hdl ) const
{
	namespace asio=websocketpp::lib::asio;
	auto pSSLContext=std::make_shared<websocketpp::lib::asio::ssl::context>(asio::ssl::context::tlsv12);
	// Try and copy the "intermediate" SSL (actually TLS) settings from
	// https://mozilla.github.io/server-side-tls/ssl-config-generator/. There's
	// not an OpenSSL option but you can infer most of the options from the other
	// configurations.
	pSSLContext->set_options( asio::ssl::context::default_workarounds |
	                          asio::ssl::context::no_sslv2 |
	                          asio::ssl::context::no_sslv3 |
	                          asio::ssl::context::single_dh_use );
	SSL_CTX_set_cipher_list( pSSLContext->native_handle(), "ECDHE-ECDSA-CHACHA20-POLY1305:ECDHE-RSA-CHACHA20-POLY1305:"
		"ECDHE-ECDSA-AES128-GCM-SHA256:ECDHE-RSA-AES128-GCM-SHA256:ECDHE-ECDSA-AES256-GCM-SHA384:ECDHE-RSA-AES256-GCM-SHA384:"
		"DHE-RSA-AES128-GCM-SHA256:DHE-RSA-AES256-GCM-SHA384:ECDHE-ECDSA-AES128-SHA256:ECDHE-RSA-AES128-SHA256:"
		"ECDHE-ECDSA-AES128-SHA:ECDHE-RSA-AES256-SHA384:ECDHE-RSA-AES128-SHA:ECDHE-ECDSA-AES256-SHA384:"
		"ECDHE-ECDSA-AES256-SHA:ECDHE-RSA-AES256-SHA:DHE-RSA-AES128-SHA256:DHE-RSA-AES128-SHA:DHE-RSA-AES256-SHA256:"
		"DHE-RSA-AES256-SHA:ECDHE-ECDSA-DES-CBC3-SHA:ECDHE-RSA-DES-CBC3-SHA:EDH-RSA-DES-CBC3-SHA:AES128-GCM-SHA256:"
		"AES256-GCM-SHA384:AES128-SHA256:AES256-SHA256:AES128-SHA:AES256-SHA:DES-CBC3-SHA:!DSS" );

	handle_tls_init_common( pSSLContext );
	return pSSLContext;
}

websocketpp::lib::shared_ptr<websocketpp::lib::asio::ssl::context> REPLACEME_PROJECT_NAMESPACE::detail::TLSHandler::handle_tls_init_modern( websocketpp::connection_hdl hdl ) const
{
	namespace asio=websocketpp::lib::asio;
	auto pSSLContext=std::make_shared<websocketpp::lib::asio::ssl::context>(asio::ssl::context::tlsv12);
	// Try and copy the "modern" SSL (actually TLS) settings from
	// https://mozilla.github.io/server-side-tls/ssl-config-generator/. There's
	// not an OpenSSL option but you can infer most of the options from the other
	// configurations.
	pSSLContext->set_options( asio::ssl::context::default_workarounds |
	                          asio::ssl::context::no_sslv2 |
	                          asio::ssl::context::no_sslv3 |
	                          asio::ssl::context::no_tlsv1 |
	                          asio::ssl::context::no_tlsv1_1 |
	                          asio::ssl::context::single_dh_use );
	SSL_CTX_set_cipher_list( pSSLContext->native_handle(), "ECDHE-ECDSA-AES256-GCM-SHA384:ECDHE-RSA-AES256-GCM-SHA384:"
		"ECDHE-ECDSA-CHACHA20-POLY1305:ECDHE-RSA-CHACHA20-POLY1305:ECDHE-ECDSA-AES128-GCM-SHA256:ECDHE-RSA-AES128-GCM-SHA256:"
		"ECDHE-ECDSA-AES256-SHA384:ECDHE-RSA-AES256-SHA384:ECDHE-ECDSA-AES128-SHA256:ECDHE-RSA-AES128-SHA256" );

	handle_tls_init_common( pSSLContext );
	return pSSLContext;
}

void REPLACEME_PROJECT_NAMESPACE::detail::TLSHandler::handle_tls_init_common( std::shared_ptr<websocketpp::lib::asio::ssl::context> pSSLContext ) const
{
	namespace asio=websocketpp::lib::asio;

	if( passwordCallback_ ) pSSLContext->set_password_callback( passwordCallback_ );
	if( !certificateChainFileName_.empty() ) pSSLContext->use_certificate_chain_file( certificateChainFileName_ );
	if( !privateKeyFileName_.empty() ) pSSLContext->use_private_key_file( privateKeyFileName_, asio::ssl::context::pem );
	if( !verifyFileName_.empty() )
	{
		pSSLContext->set_verify_mode( asio::ssl::verify_peer | asio::ssl::verify_fail_if_no_peer_cert );
		pSSLContext->load_verify_file( verifyFileName_ );
		if( certificateVerificationCallback_ ) pSSLContext->set_verify_callback( certificateVerificationCallback_ );
	}
	else pSSLContext->set_verify_mode( asio::ssl::verify_none );
	if( !diffieHellmanParamsFileName_.empty() ) pSSLContext->use_tmp_dh_file( diffieHellmanParamsFileName_ );
}
