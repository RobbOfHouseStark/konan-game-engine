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

    Camera create_camera() {
        return konan::engine::Camera { 45.f, 1.f, 0.1f, 500.f };
    }

    void show_camera(Camera& camera) {
        ImGui::DragFloat("Fov.", &(camera.fov));
        ImGui::DragFloat("Ratio.", &(camera.ratio), 0.01f, 0.f, 3.f);
        ImGui::DragFloat("Near Clipping Plane.", &(camera.near_clipping_plane));
        ImGui::DragFloat("Far Clipping Plane..", &(camera.far_clipping_plane));
    }
}
