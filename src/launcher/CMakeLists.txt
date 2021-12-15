# SPDX-License-Identifier: BSD-2-Clause

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
