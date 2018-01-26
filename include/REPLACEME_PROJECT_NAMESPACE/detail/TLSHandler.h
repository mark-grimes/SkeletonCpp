#ifndef INCLUDEGUARD_REPLACEME_PROJECT_NAMESPACE_impl_TLSHandler_h
#define INCLUDEGUARD_REPLACEME_PROJECT_NAMESPACE_impl_TLSHandler_h

#include <functional>
#include <string>
#include <websocketpp/config/asio.hpp>

namespace REPLACEME_PROJECT_NAMESPACE
{

	namespace detail
	{
		/** @brief Methods common to Client and Server that deal with the TLS handshake.
		 *
		 * @author Mark Grimes
		 * @date 26/Jul/2015
		 */
		class TLSHandler
		{
		public:
			TLSHandler( websocketpp::config::asio::alog_type& logger );

			void setCertificateChainFile( const std::string& filename );
			void setCertificateChainFile( std::string&& filename );
			void setPrivateKeyFile( const std::string& filename );
			void setPrivateKeyFile( std::string&& filename );
			void setVerifyFile( const std::string& filename );
			void setVerifyFile( std::string&& filename );
			void setDiffieHellmanParamsFile( const std::string& filename );
			void setDiffieHellmanParamsFile( std::string&& filename );
			void setCertificateVerificationCallback( std::function<bool(bool,websocketpp::lib::asio::ssl::verify_context&)>&& function );
			void setPasswordCallback( std::function<std::string(size_t,websocketpp::lib::asio::ssl::context::password_purpose)>&& function );

			std::shared_ptr<websocketpp::lib::asio::ssl::context> handle_tls_init_intermediate( websocketpp::connection_hdl hdl ) const;
			std::shared_ptr<websocketpp::lib::asio::ssl::context> handle_tls_init_modern( websocketpp::connection_hdl hdl ) const;
		protected:
			void handle_tls_init_common( std::shared_ptr<websocketpp::lib::asio::ssl::context> pSSLContext ) const;
			std::string certificateChainFileName_;
			std::string privateKeyFileName_;
			std::string verifyFileName_;
			std::string diffieHellmanParamsFileName_;
			std::function<bool(bool,websocketpp::lib::asio::ssl::verify_context&)> certificateVerificationCallback_;
			std::function<std::string(size_t,websocketpp::lib::asio::ssl::context::password_purpose)> passwordCallback_;
			websocketpp::config::asio::alog_type& logger_;
		};

	} // end of namespace detail
} // end of namespace REPLACEME_PROJECT_NAMESPACE

#endif // end of ifndef INCLUDEGUARD_REPLACEME_PROJECT_NAMESPACE_impl_TLSHandler_h
