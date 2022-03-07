add_library(
        engine
        interpreters/creator_interpreter.hpp
        systems/render_system.cpp systems/render_system.hpp
        systems/event_system.cpp systems/event_system.hpp
        systems/script_system.cpp systems/script_system.hpp
        systems/input_system.cpp systems/input_system.hpp
        events/key.cpp events/key.hpp
        events/button.cpp events/button.hpp
        events/mouse_move.cpp events/mouse_move.hpp
        components/camera.cpp components/camera.hpp
        components/transform.cpp components/transform.hpp
        components/model.hpp components/model.cpp
        components/id.cpp components/id.hpp
        components/script.cpp components/script.hpp
        components/render_data.cpp components/render_data.hpp
)

target_include_directories(
        engine INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
        engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/interpreters
        engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/components
        engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/systems
        engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/events
)

target_link_libraries(engine ecs graphics)
