# SPDX-License-Identifier: BSD-2-Clause

cmake_minimum_required(VERSION 3.4)

project(launcher
    VERSION 0.0.1
    DESCRIPTION "Cross platform JVM game launcher."
    HOMEPAGE_URL "https://github.com/Open592/launcher"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/Modules)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
set(PROJECT_VENDOR_DIRECTORY ${PROJECT_SOURCE_DIR}/vendor)

find_program(CCACHE ccache)

if (CCACHE)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ${CCACHE})
elseif()
    message(STATUS "Could not find ccache")
endif()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(vendor)
add_subdirectory(src)
