# SPDX-License-Identifier: BSD-2-Clause

add_library(core STATIC
    AppletViewerLoader.cpp
    AppletViewerLoader.hpp
    FileSystemUtils.hpp
    Launcher.cpp
    Launcher.hpp
)

if (CMAKE_SYSTEM_NAME STREQUAL "Linux")
    target_sources(core
        PRIVATE
        platform/linux/FileSystemUtils.cpp
    )
elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    target_sources(core
        PRIVATE
        platform/windows/FileSystemUtils.cpp
    )
else()
    message(FATAL_ERROR "${CMAKE_SYSTEM_NAME} Not supported at this time")
endif()

## Find JNI components. By default this will pull from bundled JRE
include(Open592FindJNI)

target_include_directories(core PUBLIC ${JNI_INCLUDE_DIRS})
target_link_libraries(core PRIVATE ${JNI_LIBRARIES} fmt)

## Install `jvm.dll` into binary directory on Windows
if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    file(COPY ${JAVA_JVM_DLL} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
endif()
