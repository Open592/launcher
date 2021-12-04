# SPDX-License-Identifier: BSD-2-Clause

add_compile_options(
    -march=native
    -Wall
    -pedantic
    -Wextra
    -Wstrict-overflow
    -Wconversion
    -fno-strict-aliasing
    "$<$<CONFIG:DEBUG>:-g>"
    "$<$<CONFIG:DEBUG>:-pg>"
    "$<$<CONFIG:DEBUG>:-Werror>"
    "$<$<CONFIG:DEBUG>:-Wshadow>"
    "$<$<CONFIG:DEBUG>:-O0>"
    "$<$<CONFIG:RELEASE>:-O3>"
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED OFF)
set(CMAKE_CSXX_EXTENSIONS OFF)

add_executable(launcher
    main.cpp
    Launcher.cpp
)

if (UNIX)
    message(STATUS "UNIX")
else()
    message(FATAL_ERROR "At this time only unix like systems are supported.")
endif()

set_target_properties(launcher
    PROPERTIES
    VERSION ${PROJECT_VERSION}
    LANGUAGES CXX
)

## Find JNI components. By default this will pull from bundled JRE
include(Open592FindJNI)

target_include_directories(launcher PRIVATE ${JNI_INCLUDE_DIRS})
target_link_libraries(launcher PRIVATE ${JNI_LIBRARIES} fmt)

install(TARGETS launcher RUNTIME DESTINATION ${PROJECT_BINARY_DIRECTORY})
