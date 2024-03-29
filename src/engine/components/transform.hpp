#ifndef KGE_ENGINE_TRANSFORM_HPP
#define KGE_ENGINE_TRANSFORM_HPP

#define _USE_MATH_DEFINES
#include <cmath>

#include <glm/ext/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include "interpreters/imgui_interpreter.hpp"

namespace konan::engine {
    struct Transform;

    void show_transform(Transform& transform);

    struct Transform : public ImGuiInterpreter<Transform, show_transform> {
        Transform();
        Transform(float x, float y, float z);
        Transform(glm::vec3 const& position, glm::vec3 const& rotation, glm::vec3 const& scale);

        glm::vec3 forward() const;
        glm::vec3 forward(float distance) const;
        glm::vec3 right() const;
        glm::vec3 right(float distance) const;
        glm::vec3 up() const;
        glm::vec3 up(float distance) const;

        void move_forward(float distance);
        void move_right(float distance);
        void move_up(float distance);

        glm::mat4 view_matrix() const;
        glm::mat4 model_matrix() const;

    public:
        glm::vec3 position;
        glm::vec3 rotation;
        glm::vec3 scale;

    private:
        glm::mat4 translation_matrix() const;
        glm::mat4 rotation_matrix() const;
        glm::mat4 scale_matrix() const;
    };
}

#endif  // KGE_ENGINE_TRANSFORM_HPP
