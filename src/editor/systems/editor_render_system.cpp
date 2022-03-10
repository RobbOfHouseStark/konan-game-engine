#include "editor_render_system.hpp"

namespace konan::editor {
    EditorRenderSystem::EditorRenderSystem(std::shared_ptr<graphics::Renderer> renderer)
        : renderer_ { renderer } {}

    void EditorRenderSystem::init() {
        scene_world_ = world->injection<ecs::World>();
    }

    void EditorRenderSystem::run(double dt) {
        for (auto& [_, camera, render_data, camera_transform]:
                    world->filter<engine::Camera, engine::RenderData, engine::Transform>()) {
            render_data.framebuffer->bind();

            for (auto& [entity, model, transform]: scene_world_->filter<engine::Model, engine::Transform>()) {
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
    }
}
