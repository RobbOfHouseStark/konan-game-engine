#ifndef KGE_EDITOR_CUBE_HPP
#define KGE_EDITOR_CUBE_HPP

#include "engine/components/script.hpp"
#include "engine/components/transform.hpp"

namespace konan::editor {
    struct Cube : public engine::IScriptable {
        explicit Cube(float rotation_speed);

        void init() override;
        void run() override;

    private:
        float rotation_speed_;
        engine::Transform* transform_ {};
    };
}

#endif  // KGE_EDITOR_CUBE_HPP
