find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(boost REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})

add_library(my_little_engine STATIC
    #core
    core/engine.cpp
    #common
    common/vector.cpp
    #events
    events/event_handler.cpp
    #objects
    objects/game_object.cpp
    objects/scene.cpp
    objects/ui.cpp
    #rendering
    rendering/rendering_controller.cpp
    rendering/texture_renderer.cpp
    rendering/texture.cpp
    #physics
    physics/collision_manager.cpp
    physics/collision.cpp
    )

target_link_libraries(my_little_engine PUBLIC SDL2::SDL2 SDL2::SDL2main)
target_link_libraries(my_little_engine PUBLIC SDL2_image::SDL2_image)
target_link_libraries(my_little_engine PUBLIC SDL2_ttf::SDL2_ttf)

target_include_directories(my_little_engine PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")