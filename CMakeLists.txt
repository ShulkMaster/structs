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
