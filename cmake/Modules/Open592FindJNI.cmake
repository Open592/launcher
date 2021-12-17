# SPDX-License-Identifier: BSD-2-Clause

# Small implementation of FindJNI which will utilize bundled JRE if
# USE_SYSTEM_JAVA is not explicitly set.

if (USE_SYSTEM_JAVA)
    if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
        message(FATAL_ERROR "Using system JNI is not supported on Windows")
    else()
        message(WARNING "Attempting to locate JNI from system - This is not fully supported")
    endif()

    find_package(JNI REQUIRED)
else()
    set(JRE_ROOT_DIRECTORY ${PROJECT_VENDOR_DIRECTORY}/jre)

    # TODO: Handle different arch's
    if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
        set(JRE_DIRECTORY ${JRE_ROOT_DIRECTORY}/windows)
    elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
        set(JRE_DIRECTORY ${JRE_ROOT_DIRECTORY}/linux)
    elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
        set(JRE_DIRECTORY ${JRE_ROOT_DIRECTORY}/osx)
    else()
        message(FATAL_ERROR "Target OS not supported: ${CMAKE_SYSTEM_NAME}")
    endif()

    message(STATUS "Attempting to locate JNI from bundled JRE: ${JRE_DIRECTORY}")

    find_library(JAVA_JVM_LIBRARY jvm
        HINTS
        ${JRE_DIRECTORY}/lib/server
        ${JRE_DIRECTORY}/lib
        REQUIRED
    )

    find_library(JAVA_AWT_LIBRARY jawt
        HINTS
        ${JRE_DIRECTORY}/lib
        REQUIRED
    )

    if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
        find_file(JAVA_JVM_DLL jvm.dll
            HINTS
            ${JRE_DIRECTORY}/bin/server
            REQUIRED
        )

        if (JAVA_JVM_DLL-NOTFOUND)
            message(FATAL_ERROR "Failed to find jvm.dll")
        endif()

        mark_as_advanced(JAVA_JVM_DLL)
    endif()

    find_path(JAVA_INCLUDE_PATH jni.h
        HINTS
        ${JRE_DIRECTORY}/include
        REQUIRED
    )

    find_path(JAVA_INCLUDE_PATH2 NAMES jni_md.h jniport.h
        HINTS
        ${JAVA_INCLUDE_PATH}
        ${JAVA_INCLUDE_PATH}/linux
        ${JAVA_INCLUDE_PATH}/darwin
        ${JAVA_INCLUDE_PATH}/win32
        REQUIRED
    )

    find_path(JAVA_AWT_INCLUDE_PATH jawt.h
        HINTS
        ${JAVA_INCLUDE_PATH}
        ${JAVA_INCLUDE_PATH}/win32
        REQUIRED
    )

    if (JAVA_AWT_LIBRARY AND JAVA_JVM_LIBRARY AND JAVA_AWT_INCLUDE_PATH AND JAVA_INCLUDE_PATH AND JAVA_INCLUDE_PATH2)
        message(STATUS "Successfully located JNI components")

        set(JNI_FOUND TRUE)
    else()
        message(FATAL_ERROR "Failed to locate required JNI components")
    endif()


    mark_as_advanced(
        JAVA_AWT_LIBRARY
        JAVA_JVM_LIBRARY
        JAVA_AWT_INCLUDE_PATH
        JAVA_INCLUDE_PATH
        JAVA_INCLUDE_PATH2
    )

    set(JNI_LIBRARIES
        ${JAVA_AWT_LIBRARY}
        ${JAVA_JVM_LIBRARY}
    )

    set(JNI_INCLUDE_DIRS
        ${JAVA_INCLUDE_PATH}
        ${JAVA_INCLUDE_PATH2}
        ${JAVA_AWT_INCLUDE_PATH}
    )
endif()
