add_library(editor editor.cpp editor.hpp systems/camera_movement_system.cpp systems/camera_movement_system.hpp scripts/editor_cube.cpp scripts/editor_cube.hpp)
target_include_directories(
        editor INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
        editor PUBLIC ../../deps/yaml-cpp/include
)
target_link_libraries(editor PRIVATE yaml-cpp core ecs engine graphics)

add_custom_command(
        TARGET editor POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_CURRENT_SOURCE_DIR}/../../resources/shaders/default.glsl
        ${CMAKE_CURRENT_BINARY_DIR}/../resources/shaders/default.glsl
)

add_custom_command(
        TARGET editor POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_CURRENT_SOURCE_DIR}/../../resources/models/bricks.obj
        ${CMAKE_CURRENT_BINARY_DIR}/../resources/models/bricks.obj
)

add_custom_command(
        TARGET editor POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_CURRENT_SOURCE_DIR}/../../resources/textures/bricks.tga
        ${CMAKE_CURRENT_BINARY_DIR}/../resources/textures/bricks.tga
)

add_custom_command(
        TARGET editor POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_CURRENT_SOURCE_DIR}/../../resources/config.yaml
        ${CMAKE_CURRENT_BINARY_DIR}/../config.yaml
)
