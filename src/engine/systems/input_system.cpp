#include "input_system.hpp"

namespace {
    // TODO: multi window fix.
    std::optional<konan::engine::Button> s_button;
    std::optional<konan::engine::Key> s_key;

    void mouse_button_callback(int id, int action, int mods) {
        s_button = konan::engine::Button(id, action, mods);
    }

    void key_callback(auto id, auto scan_code, auto action, auto mods) {
        s_key = konan::engine::Key(id, scan_code, action, mods);
    }
}

namespace konan::engine {
    void InputSystem::init() {
        world->one_frame<Button>();
        world->one_frame<Key>();
        world->one_frame<MouseMove>();

        window_ = world->injection<graphics::Window>();
        window_->mouse_button_callback(mouse_button_callback);
        window_->key_callback(key_callback);
    }

    void InputSystem::run(double dt) {
        static ecs::Entity input { world->new_entity() };

        auto [x, y] = window_->mouse_position();
        auto dx { x - previous_x_ }, dy { y - previous_y_ };
        if (dx != 0 || dy != 0) {
            input.replace<MouseMove>(dx, dy);
            previous_x_ = x;
            previous_y_ = y;
        }

        if (s_button.has_value()) {
            input.replace<Button>(s_button.value());
            s_button.reset();
        }

        if (s_key.has_value()) {
            input.replace<Key>(s_key.value());
            s_key.reset();
        }
    }
}
