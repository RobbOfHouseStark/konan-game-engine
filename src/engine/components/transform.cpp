#include "transform.hpp"

namespace konan::engine {
    Transform::Transform(float x, float y, float z)
        : Transform({ x, y, z }, {}, { 1.f, 1.f, 1.f }) {}

    Transform::Transform(glm::vec3 const& position, glm::vec3 const& rotation, glm::vec3 const& scale)
        : position { position }, rotation { rotation }, scale { scale } {}

    glm::vec3 Transform::forward() const {
        return { glm::cos(rotation.x) * glm::sin(rotation.y),
                 glm::sin(rotation.x),
                 glm::cos(rotation.x) * glm::cos(rotation.y) };
    }

    glm::vec3 Transform::forward(float distance) const {
        return forward() * distance;
    }

    glm::vec3 Transform::right() const {
        return { std::sin(rotation.y - M_PI_2), 0, std::cos(rotation.y - M_PI_2) };
    }

    glm::vec3 Transform::right(float distance) const {
        return right() * distance;
    }

    glm::vec3 Transform::up() const {
        return glm::cross(right(), forward());
    }

    glm::vec3 Transform::up(float distance) const {
        return up() * distance;
    }

    void Transform::move_forward(float distance) {
        position += forward(distance);
    }

    void Transform::move_right(float distance) {
        position += right(distance);
    }

    void Transform::move_up(float distance) {
        position += up(distance);
    }

    glm::mat4 Transform::view_matrix() const {
        return glm::lookAt(
            position,
            position + forward(1.f),
            up()
        );
    }

    glm::mat4 Transform::model_matrix() const {
        return translation_matrix() * rotation_matrix() * scale_matrix();

    }

    glm::mat4 Transform::translation_matrix() const {
        return glm::translate(glm::mat4(1.f), position);
    }

    glm::mat4 Transform::rotation_matrix() const {
        return glm::rotate(glm::rotate(glm::rotate(
                                           glm::mat4(1.f),
                                           glm::radians(rotation.x), glm::vec3(1.f, 0.f, 0.f)),
                                       glm::radians(rotation.z), glm::vec3(0.f, 0.f, 1.f)),
                           glm::radians(rotation.y), glm::vec3(0.f, 1.f, 0.f));
    }

    glm::mat4 Transform::scale_matrix() const {
        return glm::scale(scale);
    }
}
