add_library(
        imgui
        imgui/imgui.h imgui/imgui.cpp
        imgui/imgui_demo.cpp imgui/imgui_draw.cpp
        imgui/imgui_internal.h imgui/imgui_tables.cpp
        imgui/imgui_widgets.cpp imgui/imstb_rectpack.h
        imgui/imstb_textedit.h imgui/imstb_truetype.h
        imgui/backends/imgui_impl_glfw.cpp
        imgui/backends/imgui_impl_glfw.h
        imgui/backends/imgui_impl_opengl3.cpp
        imgui/backends/imgui_impl_opengl3.h
)

target_include_directories(
        imgui PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/imgui/backends
        imgui PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/imgui/
)

target_link_libraries(imgui PRIVATE glfw)
