#include "camera_movement_system.hpp"

#include <iostream>

namespace konan::editor {
    CameraMovementSystem::CameraMovementSystem(float speed, float rotation_speed)
        : _speed { speed }, _rotation_speed { rotation_speed } {}

    void CameraMovementSystem::run() {
        for (auto& [entity, camera, transform]: _world->filter<engine::Camera, engine::Transform>()) {
            for (auto& [_, button]: _world->filter<engine::Button>()) {
                // TODO: move to config.
                if (button.id == 1)
                    _should_rotate = static_cast<bool>(button.action);
            }

            if (_should_rotate) {
                for (auto& [_, movement]: _world->filter<engine::MouseMove>()) {
                    // TODO: chg float to double everywhere.
                    transform.rotation.y -= static_cast<float>(movement.dx) * _rotation_speed;
                    transform.rotation.x += static_cast<float>(movement.dy) * _rotation_speed;
                }
            }

            for (auto& [_, key]: _world->filter<engine::Key>()) {
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
                transform.move_forward(_speed);
            if (_back)
                transform.move_forward(-_speed);
            if (_left)
                transform.move_right(-_speed);
            if (_right)
                transform.move_right(_speed);
        }
    }
}
