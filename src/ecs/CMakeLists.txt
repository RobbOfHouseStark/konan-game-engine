add_library(
        ecs
        types.hpp
        world.cpp world.hpp
        component_handler.hpp systems.cpp systems.hpp
        scene.cpp scene.hpp)

target_include_directories(ecs INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
