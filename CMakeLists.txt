cmake_minimum_required(VERSION 3.3)

set(PROJECT_NAME "ThunderEventListner")
set(DESCRIPTION "Client to listen to the events of Thunder and Thunder Plugins.")
set(DEFAULT_BUILD_TYPE "Release")

project(${PROJECT_NAME} VERSION 1.0.0 LANGUAGES CXX)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
	message(STATUS "Setting build type to '${DEFAULT_BUILD_TYPE}' as none was specified.")
	set(CMAKE_BUILD_TYPE "${DEFAULT_BUILD_TYPE}" CACHE STRING "Choose the type of build." FORCE)
	set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

find_package(PkgConfig REQUIRED)
find_package(WPEFrameworkProtocols REQUIRED)

set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 11
    CXX_STANDARD_REQUIRED YES
    )

include(GNUInstallDirs)

target_include_directories(${CMAKE_CURRENT_SOURCE_DIR} PRIVATE ${WPEFrameworkProtocols_INCLUDE_DIRS})

add_executable(${PROJECT_NAME} thunderEventListner.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE
    WPEFrameworkProtocols::WPEFrameworkProtocols)

# Install products
install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
