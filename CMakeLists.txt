cmake_minimum_required(VERSION 3.3)

set(PROJECT_NAME "ENTSRVICECOMRPCTestClients")
set(DESCRIPTION "EntServices COMRPC Client to test the COMRPC implementation.")
set(DEFAULT_BUILD_TYPE "Release")

project(${PROJECT_NAME} VERSION 1.0.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

set(TESTBINPREFIX "ComRPCPlugin")
set(MODULE_NAME ${TESTBINPREFIX})

option(FRAMERATETESTAPP "Enable Framerate test application" OFF)
option(DEVICEINFOTESTAPP "Enable DeviceInfo test application" OFF)
option(DISPLAYINFOTESTAPP "Enable DisplayInfo test application" OFF)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(STATUS "Setting build type to '${DEFAULT_BUILD_TYPE}' as none was specified.")
    set(CMAKE_BUILD_TYPE "${DEFAULT_BUILD_TYPE}" CACHE STRING "Choose the type of build." FORCE)
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

find_package(PkgConfig REQUIRED)
pkg_check_modules(WPEFRAMEWORKCORE REQUIRED WPEFrameworkCore)
pkg_check_modules(WPEFRAMEWORKWEBSOCKET REQUIRED WPEFrameworkWebSocket)
pkg_check_modules(WPEFRAMEWORKDEFINITIONS REQUIRED WPEFrameworkDefinitions)
pkg_check_modules(WPEFRAMEWORKPLUGINS REQUIRED WPEFrameworkPlugins)

set(COMMON_INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${WPEFRAMEWORKCORE_INCLUDE_DIRS}
    ${WPEFRAMEWORKWEBSOCKET_INCLUDE_DIRS}
    ${WPEFRAMEWORKDEFINITIONS_INCLUDE_DIRS}
    ${WPEFRAMEWORKPLUGINS_INCLUDE_DIRS}
    )

set(COMMON_LIBRARIES
    ${WPEFRAMEWORKCORE_LIBRARIES}
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
    set(FRAMERATE_EXECUTABLE_NAME "${TESTBINPREFIX}FrameRateTest")
    add_executable(${FRAMERATE_EXECUTABLE_NAME} entServicesCOMRPC-FrameRateTest.cpp)
    target_compile_definitions(${FRAMERATE_EXECUTABLE_NAME} PUBLIC MODULE_NAME=${FRAMERATE_EXECUTABLE_NAME})
    target_include_directories(${FRAMERATE_EXECUTABLE_NAME} PRIVATE ${COMMON_INCLUDE_DIRS})
    target_link_libraries(${FRAMERATE_EXECUTABLE_NAME} PRIVATE ${COMMON_LIBRARIES})
    list(APPEND TEST_TARGETS ${FRAMERATE_EXECUTABLE_NAME})
else()
    message(STATUS "Framerate test application is disabled.")
endif()

if (DEVICEINFOTESTAPP)
    message(STATUS "DeviceInfo test application is enabled.")
    set(DEVICEINFO_EXECUTABLE_NAME "${TESTBINPREFIX}DeviceInfoTest")
    add_executable(${DEVICEINFO_EXECUTABLE_NAME} entServicesCOMRPC-DeviceInfoTest.cpp)
    target_compile_definitions(${DEVICEINFO_EXECUTABLE_NAME} PUBLIC MODULE_NAME=${DEVICEINFO_EXECUTABLE_NAME})
    target_include_directories(${DEVICEINFO_EXECUTABLE_NAME} PRIVATE ${COMMON_INCLUDE_DIRS})
    target_link_libraries(${DEVICEINFO_EXECUTABLE_NAME} PRIVATE ${COMMON_LIBRARIES})
    list(APPEND TEST_TARGETS ${DEVICEINFO_EXECUTABLE_NAME})
else()
    message(STATUS "DeviceInfo test application is disabled.")
endif()

if (DISPLAYINFOTESTAPP)
	message(STATUS "DisplayInfo test application is enabled.")
	set(DISPLAYINFO_EXECUTABLE_NAME "${TESTBINPREFIX}DisplayInfoTest")
	add_executable(${DISPLAYINFO_EXECUTABLE_NAME} entServicesCOMRPC-DisplayInfoTest.cpp)
	target_compile_definitions(${DISPLAYINFO_EXECUTABLE_NAME} PUBLIC MODULE_NAME=${DISPLAYINFO_EXECUTABLE_NAME})
	target_include_directories(${DISPLAYINFO_EXECUTABLE_NAME} PRIVATE ${COMMON_INCLUDE_DIRS})
	target_link_libraries(${DISPLAYINFO_EXECUTABLE_NAME} PRIVATE ${COMMON_LIBRARIES})
	list(APPEND TEST_TARGETS ${DISPLAYINFO_EXECUTABLE_NAME})
else()
	message(STATUS "DisplayInfo test application is disabled.")

# Install dynamically added targets
if (TEST_TARGETS)
    install(TARGETS ${TEST_TARGETS} RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
else()
    message(STATUS "No test applications enabled for installation.")
endif()
