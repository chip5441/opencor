/*******************************************************************************

Licensed to the OpenCOR team under one or more contributor license agreements.
See the NOTICE.txt file distributed with this work for additional information
regarding copyright ownership. The OpenCOR team licenses this file to you under
the Apache License, Version 2.0 (the "License"); you may not use this file
except in compliance with the License. You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software distributed
under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
CONDITIONS OF ANY KIND, either express or implied. See the License for the
specific language governing permissions and limitations under the License.

*******************************************************************************/

//==============================================================================
// SED-ML API disable warnings
//==============================================================================

#if !defined(SEDMLAPIENABLEWARNINGS_H) && !defined(SEDMLAPIDISABLEWARNINGS_H)
#define SEDMLAPIDISABLEWARNINGS_H

//==============================================================================

#if defined(Q_OS_WIN)
    #pragma warning(push)
    #pragma warning(disable: 4005)
#elif defined(Q_OS_LINUX)
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wignored-qualifiers"
#elif defined(Q_OS_MAC)
    #pragma clang diagnostic push
    #pragma clang diagnostic ignored "-Wignored-qualifiers"
#else
    #error Unsupported platform
#endif

//==============================================================================

#endif

//==============================================================================
// End of file
//==============================================================================