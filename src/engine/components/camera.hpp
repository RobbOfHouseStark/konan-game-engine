#ifndef KGE_ENGINE_CAMERA_HPP
#define KGE_ENGINE_CAMERA_HPP

#include <memory>

#include <glm/glm.hpp>
#include <glm/ext/matrix_clip_space.hpp>

#include "graphics/framebuffer.hpp"

#include "creator_interpreter.hpp"

namespace konan::engine {
    struct Camera;
}

namespace {
    konan::engine::Camera create_camera();
}

namespace konan::engine {
    struct Camera : public CreatorInterpreter<Camera, create_camera> {
        Camera(float fov, float ratio, float near_clipping_plane, float far_clipping_plane);

        glm::mat4 projection_matrix() const;

    public:
        float fov, ratio;
        float near_clipping_plane, far_clipping_plane;
    };
}

namespace {
    konan::engine::Camera create_camera() {
        return konan::engine::Camera { 45.f, 1.f, 0.1f, 500.f };
    }
}

#endif  // KGE_ENGINE_CAMERA_HPP
