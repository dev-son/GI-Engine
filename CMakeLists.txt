cmake_minimum_required(VERSION 3.20)

project(winapi_starter LANGUAGES CXX)

add_executable(winapi_starter WIN32
    src/Game.cpp
    src/GameAPI.cpp
    src/main.cpp
)

target_compile_features(winapi_starter PRIVATE cxx_std_17)
target_compile_definitions(winapi_starter PRIVATE UNICODE _UNICODE)

if(MSVC)
    target_compile_options(winapi_starter PRIVATE /W4 /permissive-)
else()
    target_compile_options(winapi_starter PRIVATE -Wall -Wextra -Wpedantic)
endif()
