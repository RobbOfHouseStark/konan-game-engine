#include "editor_camera.hpp"

namespace konan::editor {
    EditorCamera::EditorCamera(float speed, float rotation_speed)
        : _speed { speed }, _rotation_speed { rotation_speed } {}

    void EditorCamera::init() {
        _transform = &entity->get<engine::Transform>();
    }

    void EditorCamera::run() {
        for (auto& [_, button]: world->filter<engine::Button>()) {
            // TODO: move to config.
            if (button.id == 1)
                _should_rotate = static_cast<bool>(button.action);
        }

        if (_should_rotate) {
            for (auto& [_, movement]: world->filter<engine::MouseMove>()) {
                // TODO: chg float to double everywhere.
                _transform->rotation.y -= static_cast<float>(movement.dx) * _rotation_speed;
                _transform->rotation.x += static_cast<float>(movement.dy) * _rotation_speed;
            }
        }

        for (auto& [_, key]: world->filter<engine::Key>()) {
            // TODO: move to config.
            if (key.id == 'W')
                _forward = static_cast<bool>(key.action);
            if (key.id == 'S')
                _back = static_cast<bool>(key.action);
            if (key.id == 'A')
                _left = static_cast<bool>(key.action);
            if (key.id == 'D')
                _right = static_cast<bool>(key.action);
        }

        if (_forward)
            _transform->move_forward(_speed);
        if (_back)
            _transform->move_forward(-_speed);
        if (_left)
            _transform->move_right(-_speed);
        if (_right)
            _transform->move_right(_speed);
    }
}
