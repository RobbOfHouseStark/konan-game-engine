#include "camera_movement_system.hpp"

namespace konan::editor {
    CameraMovementSystem::CameraMovementSystem(float speed, float rotation_speed)
        : _speed { speed }, _rotation_speed { rotation_speed } {}

    void CameraMovementSystem::run() {
        _world->filter<engine::Camera, engine::Transform>(
            [this](auto _, engine::Camera& camera, engine::Transform& transform) {
                _world->filter<engine::Button>([this](auto _, engine::Button& button) {
                    // TODO: move to config.
                    if (button.id == 1)
                        _should_rotate = static_cast<bool>(button.action);
                });

                _world->filter<engine::MouseMove>([this, &transform](auto _, engine::MouseMove& movement) {
                    if (!_should_rotate)
                        return;

                    // TODO: chg float to double everywhere.
                    transform.rotation.y -= static_cast<float>(movement.dx) * _rotation_speed;
                    transform.rotation.x -= static_cast<float>(movement.dy) * _rotation_speed;
                });

                _world->filter<engine::Key>(
                    [this, &transform](auto _, engine::Key& key) {
                        if (key.action == 2)
                            return;

                        // TODO: move to config.
                        if (key.id == 'W')
                            _forward = static_cast<bool>(key.action);
                        if (key.id == 'S')
                            _back = static_cast<bool>(key.action);
                        if (key.id == 'A')
                            _left = static_cast<bool>(key.action);
                        if (key.id == 'D')
                            _right = static_cast<bool>(key.action);
                    });

                if (_forward)
                    transform.move_forward(_speed);
                if (_back)
                    transform.move_forward(-_speed);
                if (_left)
                    transform.move_right(-_speed);
                if (_right)
                    transform.move_right(_speed);
            });
    }
}
