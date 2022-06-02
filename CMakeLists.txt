cmake_minimum_required(VERSION 3.16)
project(redemption)

set(CMAKE_CXX_STANDARD 14)

add_executable(redemption)

target_include_directories(redemption PUBLIC
        data
        )

target_sources(redemption PUBLIC
        main.cpp
        )
