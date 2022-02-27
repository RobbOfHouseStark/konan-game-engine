#include "camera.hpp"

namespace konan::engine {
    Camera::Camera(float fov, float ratio, float near_clipping_plane, float far_clipping_plane,
                   std::shared_ptr<graphics::Framebuffer> framebuffer)
        : fov { fov }, ratio { ratio },
          near_clipping_plane { near_clipping_plane }, far_clipping_plane { far_clipping_plane },
          framebuffer { framebuffer } {}

    glm::mat4 Camera::projection_matrix() const {
        return glm::perspective(
            glm::radians(fov),
            ratio,
            near_clipping_plane,
            far_clipping_plane
        );
    }
}
