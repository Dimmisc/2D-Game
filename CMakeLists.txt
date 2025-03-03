cmake_minimum_required(VERSION 3.30)
project(Simgame_by_VScode)

find_package(SDL2 REQUIRED)

set(CMAKE_CXX_STANDARD 20)

add_executable(Simgame_by_VScode Main.c)

find_package(SDL2)
find_package(SDL2_image)
# find_package(SDL2_ttf)

target_link_libraries(Simgame_by_VScode SDL2::SDL2)
target_link_libraries(Simgame_by_VScode SDL2_image::SDL2_image) #FactoryZoneCE
# target_link_libraries(Simgame_by_VScode SDL2_ttf::SDL2_ttf)
