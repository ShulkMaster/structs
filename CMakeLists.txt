cmake_minimum_required(VERSION 3.16)
project(redemption)

set(CMAKE_CXX_STANDARD 14)

add_executable(unicorn)

target_include_directories(unicorn PUBLIC
        app
        entities
        data
        )

target_sources(unicorn PUBLIC
        main.cpp
        )

add_custom_target(data ALL
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_CURRENT_SOURCE_DIR}/data.txt
        $<TARGET_FILE_DIR:unicorn>/data.txt
        )

add_dependencies(data unicorn)