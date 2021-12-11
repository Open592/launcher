# SPDX-License-Identifier: BSD-2-Clause

add_subdirectory(core)
add_subdirectory(launcher)

if (ENABLE_TESTING)
    add_subdirectory(tests)
endif()
