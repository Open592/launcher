# SPDX-License-Identifier: BSD-2-Clause

find_package(Java REQUIRED)
include(UseJava)
include(GoogleTest)

set(TEST_CONFIG_DIRECTORY "${CMAKE_BINARY_DIR}/_test-config")
set(MOCK_PROJECT_CONFIG_DIRECTORY "${TEST_CONFIG_DIRECTORY}/open592")
file(MAKE_DIRECTORY ${MOCK_PROJECT_CONFIG_DIRECTORY})

add_jar(mockopen592appletviewer
    SOURCES mocks/MockOpen592AppletViewer.java
    ENTRYPOINT MockOpen592AppletViewer
    MANIFEST mocks/MockOpen592AppletViewer.MF
    OUTPUT_DIR ${MOCK_PROJECT_CONFIG_DIRECTORY}
)

# Create `.prm` file
get_target_property(JAR_CLASS_PATH mockopen592appletviewer JAR_FILE)
set(JAVA_CLASS MockOpen592AppletViewer)

configure_file(
    templates/parameters.prm.in
    "${MOCK_PROJECT_CONFIG_DIRECTORY}/parameters.prm"
)

add_executable(
    launcher_test
    launcher_test.cpp
)

target_compile_definitions(launcher_test
    PUBLIC "MOCK_PROJECT_CONFIG_DIRECTORY=\"${MOCK_PROJECT_CONFIG_DIRECTORY}\""
)

target_include_directories(launcher_test
    PRIVATE ${CMAKE_SOURCE_DIR}/src
)
target_link_libraries(launcher_test
    PRIVATE core gtest_main
)

gtest_discover_tests(launcher_test PROPERTIES ENVIRONMENT "XDG_CONFIG_HOME=${TEST_CONFIG_DIRECTORY}")
