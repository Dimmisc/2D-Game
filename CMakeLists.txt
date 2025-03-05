cmake_minimum_required(VERSION 3.30)
project(2D-Game)

find_package(SDL2 REQUIRED)

set(CMAKE_CXX_STANDARD 20)

add_executable(2D-Game Main.c)

find_package(SDL2)
find_package(SDL2_image)
# find_package(SDL2_ttf)

target_link_libraries(2D-Game SDL2::SDL2)
target_link_libraries(2D-Game SDL2_image::SDL2_image)
# target_link_libraries(2D-Game SDL2_ttf::SDL2_ttf)
