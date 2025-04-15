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
    set(FRAMERATE_EXECUTABLE_NAME "${TESTBINPREFIX}-Framerate")
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
    set(DEVICEINFO_EXECUTABLE_NAME "${TESTBINPREFIX}-DeviceInfo")
    add_executable(${DEVICEINFO_EXECUTABLE_NAME} entServicesCOMRPC-DeviceInfoTest.cpp)
    target_include_directories(${DEVICEINFO_EXECUTABLE_NAME} PRIVATE ${COMMON_INCLUDE_DIRS})
    target_link_libraries(${DEVICEINFO_EXECUTABLE_NAME} PRIVATE ${COMMON_LIBRARIES})
    target_compile_definitions(${DEVICEINFO_EXECUTABLE_NAME} PRIVATE MODULE_NAME=\"${DEVICEINFO_EXECUTABLE_NAME}\")
    list(APPEND TEST_TARGETS ${DEVICEINFO_EXECUTABLE_NAME})
else()
    message(STATUS "DeviceInfo test application is disabled.")
endif()

# Install dynamically added targets
if (TEST_TARGETS)
    install(TARGETS ${TEST_TARGETS} RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
else()
    message(STATUS "No test applications enabled for installation.")
endif()
