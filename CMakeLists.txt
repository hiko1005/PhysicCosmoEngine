cmake_minimum_required(VERSION 3.12)

project(CosmoEngine LANGUAGES C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(SDL2_DIR "${PROJECT_SOURCE_DIR}/external/SDL2-2.30.11/cmake")

find_package(SDL2 REQUIRED CONFIG)

add_executable(CosmoEngine
    src/main.c
    src/physic.c
    src/renderer.c
)

target_include_directories(CosmoEngine PRIVATE
    ${PROJECT_SOURCE_DIR}/lib
    ${PROJECT_SOURCE_DIR}/external/SDL2-2.30.11/x86_64-w64-mingw32/include
)

target_link_libraries(CosmoEngine PRIVATE
    SDL2::SDL2main
    SDL2::SDL2
)