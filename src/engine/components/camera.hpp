#ifndef KGE_ENGINE_CAMERA_HPP
#define KGE_ENGINE_CAMERA_HPP

#include <memory>

#include <glm/glm.hpp>
#include <glm/ext/matrix_clip_space.hpp>

#include "framebuffer.hpp"

namespace konan::engine {
    struct Camera {
        Camera(float fov, float ratio, float near_clipping_plane, float far_clipping_plane,
               std::shared_ptr<graphics::Framebuffer> framebuffer);

        glm::mat4 projection_matrix() const;

    public:
        float fov, ratio;
        float near_clipping_plane, far_clipping_plane;
        std::shared_ptr<graphics::Framebuffer> framebuffer;
    };
}

#endif  // KGE_ENGINE_CAMERA_HPP
