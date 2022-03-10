#include "editor_camera.hpp"

namespace konan::editor {
    EditorCamera::EditorCamera(float speed, float rotation_speed)
        : speed_ { speed }, rotation_speed_ { rotation_speed } {}

    void EditorCamera::init() {
        transform_ = &entity->get<engine::Transform>();
    }

    void EditorCamera::run(double dt) {
        for (auto& [_, button]: world->filter<engine::Button>()) {
            // TODO: move to config.
            if (button.id == 1)
                should_rotate_ = static_cast<bool>(button.action);
        }

        if (should_rotate_) {
            for (auto& [_, movement]: world->filter<engine::MouseMove>()) {
                // TODO: chg float to double everywhere.
                transform_->rotation.y -= static_cast<float>(movement.dx) * rotation_speed_;
                transform_->rotation.x += static_cast<float>(movement.dy) * rotation_speed_;
            }
        }

        for (auto& [_, key]: world->filter<engine::Key>()) {
            // TODO: move to config.
            if (key.id == 'W')
                forward_ = static_cast<bool>(key.action);
            if (key.id == 'S')
                back_ = static_cast<bool>(key.action);
            if (key.id == 'A')
                left_ = static_cast<bool>(key.action);
            if (key.id == 'D')
                right_ = static_cast<bool>(key.action);
        }

        if (forward_)
            transform_->move_forward(speed_);
        if (back_)
            transform_->move_forward(-speed_);
        if (left_)
            transform_->move_right(-speed_);
        if (right_)
            transform_->move_right(speed_);
    }
}
