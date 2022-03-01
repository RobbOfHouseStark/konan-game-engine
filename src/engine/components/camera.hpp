#ifndef KGE_ENGINE_CAMERA_HPP
#define KGE_ENGINE_CAMERA_HPP

#include <memory>

#include <glm/glm.hpp>
#include <glm/ext/matrix_clip_space.hpp>

#include "framebuffer.hpp"

namespace konan::engine {
    struct Camera {
        Camera();
        Camera(float fov, float ratio, float near_clipping_plane, float far_clipping_plane);

        glm::mat4 projection_matrix() const;

    public:
        float fov, ratio;
        float near_clipping_plane, far_clipping_plane;
    };
}

#endif  // KGE_ENGINE_CAMERA_HPP
