# SPDX-License-Identifier: BSD-2-Clause

find_package(Java REQUIRED)
include(UseJava)
include(GoogleTest)

add_jar(mockopen592appletviewer
    SOURCES MockOpen592AppletViewer.java
    ENTRYPOINT MockOpen592AppletViewer
    MANIFEST MockOpen592AppletViewer.MF
    OUTPUT_DIR ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
)

get_target_property(MAV_JAR mockopen592appletviewer JAR_FILE)
get_target_property(MAV_CLASSDIR mockopen592appletviewer CLASSDIR)

message(STATUS ${MAV_JAR})
message(STATUS ${MAV_CLASSDIR})

add_executable(
    launcher_test
    launcher_test.cpp
)

target_link_libraries(
    launcher_test
    gtest_main
)

gtest_discover_tests(launcher_test)
