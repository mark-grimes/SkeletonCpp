/*
 * Copyright 2018 Mark Grimes
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
 * associated documentation files (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge, publish, distribute,
 * sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or
 * substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT
 * NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

/** @file
 * @brief Header definition of a class to handle TLS handshakes for both client and server.
 *
 * Requires that OpenSSL has been found by the build system, otherwise the definition is ifdef out.
 *
 * The canonical location of this file is
 * https://github.com/mark-grimes/SkeletonCpp/blob/websockets/include/REPLACEME_PROJECT_NAMESPACE/detail/TLSHandler.h
 *
 * @author Mark Grimes
 * @copyright Copyright 2018 Mark Grimes. Released under the MIT licence.
 */
#ifndef ENCRYPTED_WEBSOCKETS_AVAILABLE
#	warning "TLSHandler cannot be used if OpenSSL is not part of the project"
#else

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

#endif // end of "#ifndef INCLUDEGUARD_REPLACEME_PROJECT_NAMESPACE_impl_TLSHandler_h"
#endif // end of ifndef "#ifdef ENCRYPTED_WEBSOCKETS_AVAILABLE"
