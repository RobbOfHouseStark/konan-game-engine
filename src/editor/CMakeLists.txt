cmake_minimum_required(VERSION 3.21)
project(kge_editor)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(../../deps/glad glad)
add_subdirectory(../../deps/glm glm)
add_subdirectory(../core core)
add_subdirectory(../ecs ecs)
add_subdirectory(../engine engine)
add_subdirectory(../graphics graphics)
add_executable(${PROJECT_NAME} main.cpp editor.cpp editor.hpp)
target_link_libraries(${PROJECT_NAME} PRIVATE core ecs engine graphics)

add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_CURRENT_SOURCE_DIR}/../../resources/shaders/default.glsl
        ${CMAKE_CURRENT_BINARY_DIR}/resources/shaders/default.glsl
)

add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_CURRENT_SOURCE_DIR}/../../resources/models/bricks.obj
        ${CMAKE_CURRENT_BINARY_DIR}/resources/models/bricks.obj
)

add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_CURRENT_SOURCE_DIR}/../../resources/textures/bricks.tga
        ${CMAKE_CURRENT_BINARY_DIR}/resources/textures/bricks.tga
)
