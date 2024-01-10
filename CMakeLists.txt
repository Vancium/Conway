cmake_minimum_required(VERSION 3.5)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")

set(CMAKE_CXX_STANDARD 17)

project(Conway)
find_package(SDL2)

set(
    PROJECT_SRC_FILES
    src/main.cpp
    src/Engine/Engine.cpp
    src/GameBoard/GameBoard.cpp
)

add_executable(${PROJECT_NAME} ${PROJECT_SRC_FILES})

target_link_libraries(${PROJECT_NAME} SDL2::SDL2)


