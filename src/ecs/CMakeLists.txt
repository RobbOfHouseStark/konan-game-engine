add_library(
        ecs
        ecs.hpp
        types.hpp
        world.cpp world.hpp
        component_handler.hpp component_iterable.hpp component_handler.cpp
        systems.cpp systems.hpp
        entity.cpp entity.hpp
        scene.cpp scene.hpp
)

target_include_directories(ecs INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(ecs core)
