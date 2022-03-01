#include "render_system.hpp"

namespace konan::engine {
    RenderSystem::RenderSystem(std::shared_ptr<graphics::Renderer> renderer)
        : _renderer { renderer } {}

    void RenderSystem::init() {
        _window = _world->injection<graphics::Window>();
        _window->imgui_init();
    }

    void RenderSystem::run() {
        for (auto& [_, camera, render_data, camera_transform]: _world->filter<Camera, RenderData, Transform>()) {
            render_data.framebuffer->bind();
            _window->clear();

            for (auto& [entity, model, transform]: _world->filter<Model, Transform>()) {
                model.bind();
                model.shader->load_uniform("v_MVP",
                                           camera.projection_matrix() *
                                           camera_transform.view_matrix() *
                                           transform.model_matrix());
                _renderer->draw(model.shader, model.texture, model.vertex_array);
                model.unbind();
            }

            render_data.framebuffer->unbind();
        }

        _window->imgui_begin_frame();
        for (auto& [_, camera, script]: _world->filter<Camera, Script>()) {
            script.run("UI");
        }
        _window->imgui_end_frame();

        _window->swap_buffers();
    }
}
