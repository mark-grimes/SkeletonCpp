/*
 * Copyright 2019 Mark Grimes
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
 * @brief Constants describing the project version, using information from the git tags.
 *
 * These constants are filled in automatically by the build system and should always be up to date.
 *
 * The canonical location of this file is
 * https://github.com/mark-grimes/SkeletonCpp/blob/websockets/include/REPLACEME_PROJECT_NAMESPACE/version.h
 *
 * @author Mark Grimes
 * @copyright Copyright 2019 Mark Grimes. Released under the MIT licence.
 */
#ifndef INCLUDEGUARD_REPLACEME_PROJECT_NAMESPACE_version_h
#define INCLUDEGUARD_REPLACEME_PROJECT_NAMESPACE_version_h

#include <cstdint>

namespace REPLACEME_PROJECT_NAMESPACE
{
	namespace version
	{
		extern const char* GitDescribe;
		extern const char GitHash[41];
		extern const char GitShortHash[8];
		extern const uint32_t GitShortHashInt;
	} // end of namespace version
} // end of namespace REPLACEME_PROJECT_NAMESPACE

#endif
