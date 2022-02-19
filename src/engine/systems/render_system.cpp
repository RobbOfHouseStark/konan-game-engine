#include "render_system.hpp"

namespace konan::engine {
    void RenderSystem::init() {
        _window = _world->injection<graphics::Window>();
    }

    void RenderSystem::run() {
        _window->clear();

        _world->filter<Camera, Transform>(
            [this](auto entity, Camera& camera, Transform& transform) {
                _world->filter<OpenGlModel, Transform>(
                    [&camera, &camera_transform = transform](auto entity, OpenGlModel& model, Transform& transform) {
                        model.bind(0);

                        model.shader.load_uniform("v_MVP",
                                                  camera.projection_matrix() *
                                                  camera_transform.view_matrix() *
                                                  transform.model_matrix());

                        // TODO: incapsulate.
                        glDrawElements(GL_TRIANGLES,
                                       model.vertex_array.indices_size(),
                                       GL_UNSIGNED_INT,
                                       nullptr);

                        model.unbind();
                    });
            });

        _window->swap_buffers();
    }
}
