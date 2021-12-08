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

add_executable(launcher main.cpp)

set_target_properties(launcher
    PROPERTIES
    VERSION ${PROJECT_VERSION}
    LANGUAGES CXX
)

# Include /src to allow for preserving directory hierachy
target_include_directories(launcher PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(launcher PRIVATE core)

install(TARGETS launcher RUNTIME DESTINATION ${PROJECT_BINARY_DIRECTORY})
