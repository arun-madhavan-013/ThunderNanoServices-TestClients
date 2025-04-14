cmake_minimum_required(VERSION 3.3)

set(PROJECT_NAME "ENTSRVICECOMRPCTestClient")
set(DESCRIPTION "EntServices COMRPC Client to test the COMRPC implementation.")
set(DEFAULT_BUILD_TYPE "Release")

project(${PROJECT_NAME} VERSION 1.0.0 LANGUAGES CXX)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
	message(STATUS "Setting build type to '${DEFAULT_BUILD_TYPE}' as none was specified.")
	set(CMAKE_BUILD_TYPE "${DEFAULT_BUILD_TYPE}" CACHE STRING "Choose the type of build." FORCE)
	set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/")

find_package(PkgConfig REQUIRED)
find_package(WPEFramework REQUIRED)
find_package(WPEFrameworkPlugins REQUIRED)
find_package(EntServicesAPIs REQUIRED)

if (WPEFRAMEWORK_FOUND)
    message("WPEFRAMEWORK_FOUND = ${WPEFRAMEWORK_FOUND}")
    message("< ${WPEFRAMEWORK_DEFINITIONS} | ${WPEFRAMEWORK_INCLUDE_DIRS} |
        ${WPEFRAMEWORK_LIBRARIES} | ${WPEFRAMEWORK_LIBRARY_WPEFrameworkPlugins} |
        ${WPEFRAMEWORK_LIBRARY_WPEFrameworkCore} |
        ${WPEFRAMEWORK_LIBRARY_WPEFrameworkTracing} |
        ${WPEFRAMEWORK_LIBRARY_WPEFrameworkProtocols} >")
else()
    message(FATAL_ERROR "WPEFrameworkProtocols not found")
endif()

if (ENTSERVICESAPIS_FOUND)
	message("ENTSERVICESAPIS_FOUND = ${ENTSERVICESAPIS_FOUND}")
	message("< ${ENTSERVICESAPIS_INCLUDE_DIRS} | ${ENTSERVICESAPIS_LIBRARIES} >")
else()
	message(FATAL_ERROR "EntServices APIs not found")
endif()
if (WPEFRAMEWORKPLUGIN_FOUND)
	message("WPEFRAMEWORKPLUGIN_FOUND = ${WPEFRAMEWORKPLUGIN_FOUND}")
	message("< ${WPEFRAMEWORKPLUGIN_INCLUDE_DIRS} | ${WPEFRAMEWORKPLUGIN_LIBRARIES} >")
else()
	message(FATAL_ERROR "WPEFrameworkPlugins not found")
endif()

include(GNUInstallDirs)

add_executable(${PROJECT_NAME} entServicesCOMRPC-FrameRateTest.cpp)
include_directories(${CMAKE_CURRENT_SOURCE_DIR} PRIVATE
	${WPEFRAMEWORK_INCLUDE_DIRS}
	${ENTSERVICESAPIS_INCLUDE_DIRS}
	${WPEFRAMEWORKPLUGIN_INCLUDE_DIRS}
	)
target_link_libraries(${PROJECT_NAME} PRIVATE
    ${WPEFRAMEWORK_LIBRARIES}
	${WPEFRAMEWORK_LIBRARY_WPEFrameworkCore}
	${WPEFRAMEWORK_LIBRARY_WPEFrameworkTracing}
	${WPEFRAMEWORK_LIBRARY_WPEFrameworkProtocols}
	${WPEFRAMEWORK_LIBRARY_WPEFrameworkPlugins}
	)

# Install products
install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
