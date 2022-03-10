#ifndef KGE_ENGINE_CAMERA_HPP
#define KGE_ENGINE_CAMERA_HPP

#include <memory>

#include <glm/glm.hpp>
#include <glm/ext/matrix_clip_space.hpp>

#include "graphics/framebuffer.hpp"

#include "interpreters/create_interpreter.hpp"
#include "interpreters/imgui_interpreter.hpp"

namespace konan::engine {
    struct Camera;

    Camera create_camera();
    void show_camera(Camera& camera);

    struct Camera : public CreateInterpreter<Camera, create_camera>,
                    public ImGuiInterpreter<Camera, show_camera> {
        Camera(float fov, float ratio, float near_clipping_plane, float far_clipping_plane);

        glm::mat4 projection_matrix() const;

    public:
        float fov, ratio;
        float near_clipping_plane, far_clipping_plane;
    };
}

#endif  // KGE_ENGINE_CAMERA_HPP
