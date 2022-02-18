add_library(
        graphics
        window.cpp window.hpp
        opengl/gl_window.cpp opengl/gl_window.hpp
)

target_include_directories(
        graphics PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
        graphics INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/opengl
)
target_link_libraries(graphics PUBLIC glad core)

