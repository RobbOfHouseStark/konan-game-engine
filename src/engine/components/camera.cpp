#include "camera.hpp"

namespace konan::engine {
    Camera::Camera(float fov, float ratio, float near_clipping_plane, float far_clipping_plane)
        : fov { fov }, ratio { ratio },
          near_clipping_plane { near_clipping_plane }, far_clipping_plane { far_clipping_plane } {}

    glm::mat4 Camera::projection_matrix() const {
        return glm::perspective(
            glm::radians(fov),
            ratio,
            near_clipping_plane,
            far_clipping_plane
        );
    }
}
