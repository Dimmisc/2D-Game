cmake_minimum_required(VERSION 3.30)
project(2D-Game)




set(CMAKE_CXX_STANDARD 20)

add_executable(2D-Game Main.c source/SEL.c  source/Area/Area.c  source/Area/Player/Player.c  source/Area/sprites/sprite.c  source/Area/map/MapLoad.c )



find_package(SDL2)
find_package(SDL2_image)
# find_package(SDL2_ttf)

target_link_libraries(2D-Game SDL2::SDL2)
target_link_libraries(2D-Game SDL2_image::SDL2_image)
# target_link_libraries(2D-Game SDL2_ttf::SDL2_ttf)

#  set(SOURCE 
#      source/SEL.h
#      )
# include_directories(source include)
# add_executable(2D-Game ${SOURCE})
set_target_properties(2D-Game PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY_DEBUG "${PROJECT_BINARY_DIR}/../"
    RUNTIME_OUTPUT_DIRECTORY_RELEASE "${PROJECT_BINARY_DIR}/../"
)