#ifndef KGE_EDITOR_CAMERA_HPP
#define KGE_EDITOR_CAMERA_HPP

#include "ecs/ecs.hpp"
#include "engine/components/camera.hpp"
#include "engine/components/script.hpp"
#include "engine/components/transform.hpp"
#include "engine/events/button.hpp"
#include "engine/events/key.hpp"
#include "engine/events/mouse_move.hpp"

namespace konan::editor {
    struct EditorCamera : public engine::IScriptable {
        EditorCamera(float speed, float rotation_speed);

        void init() override;
        void run() override;

    private:
        float speed_;
        float rotation_speed_;

        bool should_rotate_ {};
        bool forward_ {}, back_ {}, left_ {}, right_ {};

        engine::Transform* transform_;
    };
}

#endif  // KGE_EDITOR_CAMERA_HPP
