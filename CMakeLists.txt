cmake_minimum_required(VERSION 3.3)

set(PROJECT_NAME "ENTSRVICECOMRPCTestClients")
set(DESCRIPTION "EntServices COMRPC Client to test the COMRPC implementation.")
set(DEFAULT_BUILD_TYPE "Release")
project(${PROJECT_NAME} VERSION 1.0.0 LANGUAGES CXX)

set(TESTBINPREFIX "comprpcPluginTest")
set(MODULE_NAME ${TESTBINPREFIX})

option(FRAMERATETESTAPP "Enable Framerate test application" OFF)
option(DEVICEINFOTESTAPP "Enable DeviceInfo test application" OFF)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(STATUS "Setting build type to '${DEFAULT_BUILD_TYPE}' as none was specified.")
    set(CMAKE_BUILD_TYPE "${DEFAULT_BUILD_TYPE}" CACHE STRING "Choose the type of build." FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

#list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/")

find_package(PkgConfig REQUIRED)
pkg_check_modules(WPEFRAMEWORKCORE REQUIRED WPEFrameworkCore)
pkg_check_modules(WPEFRAMEWORKPROTOCOLS REQUIRED WPEFrameworkProtocols)
pkg_check_modules(WPEFRAMEWORKWEBSOCKET REQUIRED WPEFrameworkWebSocket)
pkg_check_modules(WPEFRAMEWORKDEFINITIONS REQUIRED WPEFrameworkDefinitions)
pkg_check_modules(WPEFRAMEWORKPLUGINS REQUIRED WPEFrameworkPlugins)

set(COMMON_INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${WPEFRAMEWORKCORE_INCLUDE_DIRS}
    ${WPEFRAMEWORKPROTOCOLS_INCLUDE_DIRS}
    ${WPEFRAMEWORKWEBSOCKET_INCLUDE_DIRS}
    ${WPEFRAMEWORKDEFINITIONS_INCLUDE_DIRS}
    ${WPEFRAMEWORKPLUGINS_INCLUDE_DIRS}
)

set(COMMON_LIBRARIES
    ${WPEFRAMEWORKCORE_LIBRARIES}
    ${WPEFRAMEWORKPROTOCOLS_LIBRARIES}
    ${WPEFRAMEWORKWEBSOCKET_LIBRARIES}
    ${WPEFRAMEWORKDEFINITIONS_LIBRARIES}
    ${WPEFRAMEWORKPLUGINS_LIBRARIES}
)

message(STATUS "Common include directories: ${COMMON_INCLUDE_DIRS}")
message(STATUS "Common libraries: ${COMMON_LIBRARIES}")

include(GNUInstallDirs)

# List to hold dynamically added targets
set(TEST_TARGETS)

if (FRAMERATETESTAPP)
    message(STATUS "Framerate test application is enabled.")
    add_executable(${FRAMERATE_EXECUTABLE_NAME} entServicesCOMRPC-FrameRateTest.cpp)
    target_include_directories(${FRAMERATE_EXECUTABLE_NAME} PRIVATE ${COMMON_INCLUDE_DIRS})
    target_link_libraries(${FRAMERATE_EXECUTABLE_NAME} PRIVATE ${COMMON_LIBRARIES})
    target_compile_definitions(${FRAMERATE_EXECUTABLE_NAME} PRIVATE MODULE_NAME=\"${FRAMERATE_EXECUTABLE_NAME}\")
    list(APPEND TEST_TARGETS ${FRAMERATE_EXECUTABLE_NAME})
else()
    message(STATUS "Framerate test application is disabled.")
endif()

if (DEVICEINFOTESTAPP)
    message(STATUS "DeviceInfo test application is enabled.")
    add_executable(COMRPCTestApp entServicesCOMRPC-DeviceInfoTest.cpp)
    target_include_directories(COMRPCTestApp PRIVATE ${COMMON_INCLUDE_DIRS})
    target_link_libraries(COMRPCTestApp PRIVATE ${COMMON_LIBRARIES})
	set_target_properties(COMRPCTestApp PROPERTIES CXX_STANDARD 11 CXX_STANDARD_REQUIRED YES)
    list(APPEND TEST_TARGETS COMRPCTestApp)
else()
    message(STATUS "DeviceInfo test application is disabled.")
endif()

# Install dynamically added targets
if (TEST_TARGETS)
    install(TARGETS ${TEST_TARGETS} RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
else()
    message(STATUS "No test applications enabled for installation.")
endif()
