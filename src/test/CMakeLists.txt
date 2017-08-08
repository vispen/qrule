# Copyright (C) 2017 Pelagicore
#
# You may use this file under the terms of the GPLv3 license.
# See the file LICENSE from this package for details.
#
# SPDX-License-Identifier: GPL-3.0

cmake_minimum_required(VERSION 3.3)
set(SOURCE_FILES
    main.cpp
    )
include_directories(.)

add_executable(QRuleTest ${SOURCE_FILES} )

find_package(Qt5Core REQUIRED)
target_link_libraries(QRuleTest ${Qt5Core_LIBRARIES})

if (${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    set (source "${CMAKE_SOURCE_DIR}/src/resources")
    set (destination "${PROJECT_BINARY_DIR}/resources")
    add_custom_command(
     TARGET QRuleTest POST_BUILD
     COMMAND ${CMAKE_COMMAND} -E create_symlink ${source} ${destination}
     DEPENDS ${destination}
     COMMENT "symbolic link resources folder from ${source} => ${destination}"
)
else()
    message(WARNING "Resource folder needs to be copied to build folder for tests to run.")
endif()

