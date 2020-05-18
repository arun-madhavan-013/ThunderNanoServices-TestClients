# If not stated otherwise in this file or this component's license file the
# following copyright and licenses apply:
#
# Copyright 2020 RDK Management
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

# - Try to find WPEFramework
# Once done this will define
#  WPEFRAMEWORK_FOUND - System has WPEFramework
#  WPEFRAMEWORK_INCLUDE_DIRS - The WPEFramework include directories
#  WPEFRAMEWORK_LIBRARIES - The libraries needed to use WPEFramework
#
# Be extremely careful! WPEFRAMEWORK_PLUGINS_INCLUDE_DIRS and WPEFRAMEWORK_LIBRARIES is already defined in
# WPEFramework/Source/plugins!!
# So here we purposely left one underscore away

find_package(PkgConfig)
pkg_check_modules(PC_WPEFRAMEWORK WPEFrameworkCore)

if(PC_WPEFRAMEWORK_FOUND)
    if(WPEFRAMEWORK_FIND_VERSION AND PC_WPEFRAMEWORK_VERSION)
        if ("${WPEFRAMEWORK_FIND_VERSION}" VERSION_GREATER "${PC_WPEFRAMEWORK_VERSION}")
            message(WARNING "Incorrect version, found ${PC_WPEFRAMEWORK_VERSION}, need at least ${WPEFRAMEWORK_FIND_VERSION}, please install correct version ${WPEFRAMEWORK_FIND_VERSION}")
            set(WPEFRAMEWORK_FOUND_TEXT "Found incorrect version")
            unset(PC_WPEFRAMEWORK_FOUND)
        endif()
    endif()
else()
    set(WPEFRAMEWORK_FOUND_TEXT "Not found")
endif()

if(PC_WPEFRAMEWORK_FOUND)
    find_path(
        WPEFRAMEWORK_INCLUDE_DIRS
        NAMES plugins/plugins.h
        HINTS ${PC_WPEFRAMEWORK_INCLUDEDIR} ${PC_WPEFRAMEWORK_INCLUDE_DIRS})

    set(WPEFRAMEWORK_LIBS WPEFrameworkPlugins WPEFrameworkCore WPEFrameworkTracing WPEFrameworkProtocols)
    set(WPEFRAMEWORK_LIBRARY )
    foreach(LIB ${WPEFRAMEWORK_LIBS})
        find_library(WPEFRAMEWORK_LIBRARY_${LIB} NAMES ${LIB}
            HINTS ${PC_WPEFRAMEWORK_LIBDIR} ${PC_WPEFRAMEWORK_LIBRARY_DIRS})
        list(APPEND WPEFRAMEWORK_LIBRARY ${WPEFRAMEWORK_LIBRARY_${LIB}})
    endforeach()

    if("${WPEFRAMEWORK_INCLUDE_DIRS}" STREQUAL "" OR "${WPEFRAMEWORK_LIBRARY}" STREQUAL "")
        set(WPEFRAMEWORK_FOUND_TEXT "Not found")
    else()
        set(WPEFRAMEWORK_FOUND_TEXT "Found")
    endif()
else()
    set(WPEFRAMEWORK_FOUND_TEXT "Not found")
endif()

if (WPEFRAMEWORK_VERBOSE_BUILD)
    message(STATUS "WPEFramework   : ${WPEFRAMEWORK_FOUND_TEXT}")
    message(STATUS "  version      : ${PC_WPEFRAMEWORK_VERSION}")
    message(STATUS "  cflags       : ${PC_WPEFRAMEWORK_CFLAGS}")
    message(STATUS "  cflags other : ${PC_WPEFRAMEWORK_CFLAGS_OTHER}")
    message(STATUS "  include dirs : ${PC_WPEFRAMEWORK_INCLUDE_DIRS} ${PC_WPEFRAMEWORK_INCLUDEDIR}")
    message(STATUS "  lib dirs     : ${PC_WPEFRAMEWORK_LIBRARY_DIRS} ${PC_WPEFRAMEWORK_LIBDIR}")
    message(STATUS "  include dirs : ${WPEFRAMEWORK_INCLUDE_DIRS}")
    message(STATUS "  libs         : ${WPEFRAMEWORK_LIBRARY}")
endif()

set(WPEFRAMEWORK_DEFINITIONS ${PC_WPEFRAMEWORK_PLUGINS_CFLAGS_OTHER})
set(WPEFRAMEWORK_INCLUDE_DIR ${WPEFRAMEWORK_INCLUDE_DIRS})
set(WPEFRAMEWORK_LIBRARIES ${WPEFRAMEWORK_LIBRARY})
set(WPEFRAMEWORK_LIBRARY_DIRS ${PC_WPEFRAMEWORK_LIBRARY_DIRS})

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(WPEFRAMEWORK DEFAULT_MSG
    WPEFRAMEWORK_LIBRARIES
    WPEFRAMEWORK_INCLUDE_DIRS)

if(WPEFRAMEWORK_FOUND)
else()
    message(WARNING "Could not find WPEFramework")
endif()

mark_as_advanced(
    WPEFRAMEWORK_DEFINITIONS
    WPEFRAMEWORK_INCLUDE_DIRS
    WPEFRAMEWORK_LIBRARIES
    WPEFRAMEWORK_LIBRARY_WPEFrameworkPlugins
    WPEFRAMEWORK_LIBRARY_WPEFrameworkCore
    WPEFRAMEWORK_LIBRARY_WPEFrameworkTracing
    WPEFRAMEWORK_LIBRARY_WPEFrameworkProtocols)
