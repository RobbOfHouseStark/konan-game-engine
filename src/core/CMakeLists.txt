add_library(core logging.hpp files.cpp files.hpp exceptions.hpp assersion.hpp)
target_include_directories(core INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(core ${PUBLIC} glm)
