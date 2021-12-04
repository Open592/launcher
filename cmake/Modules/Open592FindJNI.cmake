# Small implementation of FindJNI which will utilize bundled JRE if JAVA_HOME
# is not explicitly set.

if (USE_SYSTEM_JAVA)
    message(WARNING "Attempting to locate JNI from system - This is not fully supported")

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
        ${JRE_DIRECTORY}/lib/server
        REQUIRED
    )

    find_library(JAVA_AWT_LIBRARY jawt
        ${JRE_DIRECTORY}/lib
        REQUIRED
    )

    find_path(JAVA_INCLUDE_PATH jni.h
        ${JRE_DIRECTORY}/include
        REQUIRED
    )

    find_path(JAVA_INCLUDE_PATH2 NAMES jni_md.h jniport.h
        PATHS
        ${JAVA_INCLUDE_PATH}
        ${JAVA_INCLUDE_PATH}/linux
        ${JAVA_INCLUDE_PATH}/osx
        ${JAVA_INCLUDE_PATH}/windows
        REQUIRED
    )

    find_path(JAVA_AWT_INCLUDE_PATH jawt.h
        ${JAVA_INCLUDE_PATH}
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
