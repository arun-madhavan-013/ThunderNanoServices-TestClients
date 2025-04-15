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

set(COMMON_INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${WPEFRAMEWORKCORE_INCLUDE_DIRS}
)

set(COMMON_LIBRARIES
    ${WPEFRAMEWORKCORE_LIBRARIES}
)

message(STATUS "Common include directories: ${COMMON_INCLUDE_DIRS}")
message(STATUS "Common libraries: ${COMMON_LIBRARIES}")

include(GNUInstallDirs)

# List to hold dynamically added targets
set(TEST_TARGETS)

if (FRAMERATETESTAPP)
    message(STATUS "Framerate test application is enabled.")
    add_executable(${TESTBINPREFIX}-Framerate entServicesCOMRPC-FrameRateTest.cpp)
    target_include_directories(${TESTBINPREFIX}-Framerate PRIVATE ${COMMON_INCLUDE_DIRS})
    target_link_libraries(${TESTBINPREFIX}-Framerate PRIVATE ${COMMON_LIBRARIES})
	target_compile_definitions(${TESTBINPREFIX}-Framerate PRIVATE MODULE_NAME="${TESTBINPREFIX}-Framerate")
    list(APPEND TEST_TARGETS ${TESTBINPREFIX}-Framerate)
else()
    message(STATUS "Framerate test application is disabled.")
endif()

if (DEVICEINFOTESTAPP)
    message(STATUS "DeviceInfo test application is enabled.")
    add_executable(${TESTBINPREFIX}-DeviceInfo entServicesCOMRPC-DeviceInfoTest.cpp)
    target_include_directories(${TESTBINPREFIX}-DeviceInfo PRIVATE ${COMMON_INCLUDE_DIRS})
    target_link_libraries(${TESTBINPREFIX}-DeviceInfo PRIVATE ${COMMON_LIBRARIES})
	target_compile_definitions(${TESTBINPREFIX}-DeviceInfo PRIVATE MODULE_NAME="${TESTBINPREFIX}-DeviceInfo")
    list(APPEND TEST_TARGETS ${TESTBINPREFIX}-DeviceInfo)
else()
    message(STATUS "DeviceInfo test application is disabled.")
endif()

# Install dynamically added targets
if (TEST_TARGETS)
    install(TARGETS ${TEST_TARGETS} RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
else()
    message(STATUS "No test applications enabled for installation.")
endif()
