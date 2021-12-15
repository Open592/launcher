# SPDX-License-Identifier: BSD-2-Clause

find_package(Java REQUIRED)
include(UseJava)
include(GoogleTest)

set(TEST_CONFIG_DIRECTORY "${CMAKE_BINARY_DIR}/_test-config")
set(MOCK_PROJECT_CONFIG_DIRECTORY "${TEST_CONFIG_DIRECTORY}/open592")
file(MAKE_DIRECTORY ${MOCK_PROJECT_CONFIG_DIRECTORY})

add_jar(mockopen592appletviewer
    SOURCES mocks/MockOpen592AppletViewer.java
    ENTRY_POINT MockOpen592AppletViewer
    OUTPUT_DIR ${MOCK_PROJECT_CONFIG_DIRECTORY}
)

add_jar(mockjavaexception
    SOURCES mocks/MockJavaException.java
    ENTRY_POINT MockJavaException
    OUTPUT_DIR ${MOCK_PROJECT_CONFIG_DIRECTORY}
)

# Create `.prm` file
get_target_property(HAPPY_PATH_JAR_CLASS_PATH mockopen592appletviewer JAR_FILE)
get_target_property(ERROR_CASE_JAR_CLASS_PATH mockjavaexception JAR_FILE)

configure_file(
    templates/classnotfound.prm.in
    "${MOCK_PROJECT_CONFIG_DIRECTORY}/classnotfound.prm"
)

configure_file(
    templates/happypath.prm.in
    "${MOCK_PROJECT_CONFIG_DIRECTORY}/happypath.prm"
)

configure_file(
    templates/javaerror.prm.in
    "${MOCK_PROJECT_CONFIG_DIRECTORY}/javaerror.prm"
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
