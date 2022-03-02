add_library(glfw src/glfw.cpp)
target_include_directories(glfw INTERFACE include)
target_link_directories(glfw PUBLIC lib)
target_link_libraries(glfw glfw3)
