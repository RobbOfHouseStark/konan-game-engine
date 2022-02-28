#ifndef KGE_EDITOR_CAMERA_HPP
#define KGE_EDITOR_CAMERA_HPP

#include "button.hpp"
#include "camera.hpp"
#include "ecs.hpp"
#include "key.hpp"
#include "mouse_move.hpp"
#include "script.hpp"
#include "transform.hpp"

namespace konan::editor {
    struct EditorCamera : public engine::IScriptable {
        EditorCamera(float speed, float rotation_speed);

        void init() override;
        void run() override;

    private:
        float _speed;
        float _rotation_speed;

        bool _should_rotate {};
        bool _forward {}, _back {}, _left {}, _right {};

        engine::Transform* _transform;
    };
}

#endif  // KGE_EDITOR_CAMERA_HPP
