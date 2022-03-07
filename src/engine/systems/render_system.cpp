#include "render_system.hpp"

namespace konan::engine {
    RenderSystem::RenderSystem(std::shared_ptr<graphics::Renderer> renderer)
        : renderer_ { renderer } {}

    void RenderSystem::init() {
        window_ = world->injection<graphics::Window>();
        window_->imgui_init();
    }

    void RenderSystem::run(double dt) {
        for (auto& [_, camera, render_data, camera_transform]: world->filter<Camera, RenderData, Transform>()) {
            render_data.framebuffer->bind();
            window_->clear();

            for (auto& [entity, model, transform]: world->filter<Model, Transform>()) {
                model.bind();
                model.shader->load_uniform("v_MVP",
                                           camera.projection_matrix() *
                                           camera_transform.view_matrix() *
                                           transform.model_matrix());
                renderer_->draw(model.shader, model.texture, model.vertex_array);
                model.unbind();
            }

            render_data.framebuffer->unbind();
        }

        window_->imgui_begin_frame();
        for (auto& [_, camera, script]: world->filter<Camera, Script>()) {
            script.run("UI");
        }
        window_->imgui_end_frame();

        window_->swap_buffers();
    }
}
