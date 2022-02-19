add_library(
        graphics
        window.cpp window.hpp
        opengl/gl_window.cpp opengl/gl_window.hpp
        shader.hpp opengl/gl_shader.cpp opengl/gl_shader.hpp texture.hpp opengl/gl_texture.cpp opengl/gl_texture.hpp opengl/gl_buffer.cpp opengl/gl_buffer.hpp vertex_array.hpp opengl/gl_vertex_array.cpp opengl/gl_vertex_array.hpp)

target_include_directories(
        graphics PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
        graphics INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/opengl
)
target_link_libraries(graphics PUBLIC glad glfw core)

