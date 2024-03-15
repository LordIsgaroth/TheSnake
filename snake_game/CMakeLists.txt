#find_package(SDL2 REQUIRED)
#find_package(SDL2_image REQUIRED)
#find_package(SDL2_ttf REQUIRED)
find_package(boost REQUIRED)

#message("boost lib: ${Boost_LIBRARY_DIRS}, inc: ${Boost_INCLUDE_DIR}")

#include_directories(my_little_engine)
include_directories(${Boost_INCLUDE_DIRS})

add_executable(The_Snake
    #core
    the_snake.cpp
    snake_game.cpp
    level.cpp
    #rendering
    tile_sprite_renderer.cpp
    #objects
    snake_game_objects.cpp
    field.cpp
    snake.cpp    
    #ui
    interface.cpp
    #logic
    apple_storage.cpp
    apple_spawner.cpp
    snake_event.cpp
    )

target_link_libraries(The_Snake PUBLIC my_little_engine)