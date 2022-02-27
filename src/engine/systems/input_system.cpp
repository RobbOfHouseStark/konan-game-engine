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
        _world->one_frame<Button>();
        _world->one_frame<Key>();
        _world->one_frame<MouseMove>();

        _window = _world->injection<graphics::Window>();
        _window->mouse_button_callback(mouse_button_callback);
        _window->key_callback(key_callback);
    }

    void InputSystem::run() {
        static ecs::Entity input { _world->new_entity() };

        auto [x, y] = _window->mouse_position();
        auto dx { x - _previous_x }, dy { y - _previous_y };
        if (dx != 0 || dy != 0) {
            input.replace<MouseMove>(dx, dy);
            _previous_x = x;
            _previous_y = y;
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
