#include "editor.hpp"

namespace konan::editor {
    Editor::Editor() {
//        core::load_glsl("resources/shaders/default.glsl");
//        core::load_obj("resources/models/bricks.obj");
//        core::load_tga("resources/textures/bricks.tga");

        _world->inject<graphics::Window>(graphics::opengl::make_window(800, 600, "WindoW."));

        _systems->add<engine::EventSystem>(&_running);
        _systems->add<engine::RenderSystem>();
    }
}
