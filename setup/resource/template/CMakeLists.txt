cmake_minimum_required(VERSION 3.15)

project(demo)

add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME} PRIVATE
    "main.cc"
)