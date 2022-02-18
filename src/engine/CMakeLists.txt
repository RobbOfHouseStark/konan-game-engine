add_library(
        engine
        render_system.cpp render_system.hpp
        event_system.cpp event_system.hpp
)

target_include_directories(engine INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(engine ecs graphics)
