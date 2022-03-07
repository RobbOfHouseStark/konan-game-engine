cmake_minimum_required(VERSION 3.21)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

function(copy_hpp_file source lib_name)
    add_custom_command(
            TARGET ${lib_name} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy
            ${CMAKE_CURRENT_SOURCE_DIR}/${source}
            ${CMAKE_CURRENT_BINARY_DIR}/include/${lib_name}/${source}
    )
endfunction()

project(konan-game-engine)
add_executable(${PROJECT_NAME} main.cpp)
add_subdirectory(../deps/glad glad)
add_subdirectory(../deps/glfw glfw)
add_subdirectory(../deps/glm glm)
add_subdirectory(../deps/imgui imgui)
add_subdirectory(core)
add_subdirectory(ecs)
add_subdirectory(editor)
add_subdirectory(engine)
add_subdirectory(graphics)
target_link_libraries(${PROJECT_NAME} PUBLIC glfw glad glm imgui core ecs editor engine graphics)
