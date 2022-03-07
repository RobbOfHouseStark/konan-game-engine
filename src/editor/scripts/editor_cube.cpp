#include "editor_cube.hpp"

namespace konan::editor {
    Cube::Cube(float rotation_speed)
        : rotation_speed_ { rotation_speed } {}

    void Cube::init() {
        transform_ = &entity->get<engine::Transform>();
    }

    void Cube::run() {
        transform_->rotation.x += rotation_speed_;
    }
}
