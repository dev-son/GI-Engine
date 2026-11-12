cmake_minimum_required(VERSION 3.20)

project(GI_Engine LANGUAGES CXX)

add_executable(GI-Engine WIN32
    src/Game.cpp
    src/GameAPI.cpp
    src/main.cpp
)

target_compile_features(GI-Engine PRIVATE cxx_std_17)
target_compile_definitions(GI-Engine PRIVATE UNICODE _UNICODE)

if(MSVC)
    target_compile_options(GI-Engine PRIVATE /W4 /permissive-)
else()
    target_compile_options(GI-Engine PRIVATE -Wall -Wextra -Wpedantic)
endif()
