#ifndef KGE_EDITOR_CAMERA_MOVEMENT_SYSTEM_HPP
#define KGE_EDITOR_CAMERA_MOVEMENT_SYSTEM_HPP

#include "button.hpp"
#include "camera.hpp"
#include "key.hpp"
#include "mouse_move.hpp"
#include "transform.hpp"
#include "ecs.hpp"

namespace konan::editor {
    struct CameraMovementSystem : public ecs::IRunSystem {
        CameraMovementSystem(float speed, float rotation_speed);

        void run() override;

    private:
        float _speed;
        float _rotation_speed;

        bool _should_rotate {};
        bool _forward {}, _back {}, _left {}, _right {};
    };
}

#endif  // KGE_EDITOR_CAMERA_MOVEMENT_SYSTEM_HPP
