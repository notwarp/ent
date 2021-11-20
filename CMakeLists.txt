cmake_minimum_required(VERSION 3.20)
project(Ent C)

set(CMAKE_C_STANDARD 99)
if(CMAKE_BUILD_TYPE MATCHES Debug)
    add_compile_definitions(DEBUG)
endif()

add_subdirectory(console)
add_subdirectory(types)
add_subdirectory(window)

add_executable(Ent main.c)
target_link_libraries(Ent PUBLIC console types window)
