# SPDX-License-Identifier: BSD-2-Clause

add_library(core STATIC
    AppletViewerLoader.cpp
    AppletViewerLoader.hpp
    FileSystemUtils.hpp
    Launcher.cpp
    Launcher.hpp
)

if (UNIX AND NOT APPLE)
    target_sources(core
        PRIVATE
        platform/linux/FileSystemUtils.cpp
    )
else()
    message(FATAL_ERROR "At this time only unix like systems are supported.")
endif()

## Find JNI components. By default this will pull from bundled JRE
include(Open592FindJNI)

target_include_directories(core PUBLIC ${JNI_INCLUDE_DIRS})
target_link_libraries(core PRIVATE ${JNI_LIBRARIES} fmt)
