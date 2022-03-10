#include "ui_system.hpp"

namespace konan::engine {
    void UISystem::init() {
        window_ = world->injection<graphics::Window>();
    }

    void UISystem::run(double dt) {
        window_->imgui_begin_frame();

        for (auto& [_, camera, script]: world->filter<Camera, Script>())
            script.run(dt, "UI");

        window_->imgui_end_frame();
    }
}
