#include "render_system.hpp"

namespace konan::engine {
    RenderSystem::RenderSystem(std::shared_ptr<graphics::Renderer> renderer)
        : _renderer { renderer } {}

    void RenderSystem::init() {
        _window = _world->injection<graphics::Window>();
        _window->init_imgui();
    }

    void RenderSystem::run() {
        for (auto& [camera_entity, camera, camera_transform]: _world->filter<Camera, Transform>()) {
            camera.framebuffer->bind();
            _window->clear();

            for (auto& [model_entity, model, model_transform]: _world->filter<Model, Transform>()) {
                model.bind();

                model.shader->load_uniform("v_MVP",
                                           camera.projection_matrix() *
                                           camera_transform.view_matrix() *
                                           model_transform.model_matrix());

                _renderer->draw(model.shader, model.texture, model.vertex_array);

                model.unbind();
            }

            camera.framebuffer->unbind();

            render_ui(camera.framebuffer);
        }

        _window->swap_buffers();
    }

    void RenderSystem::render_ui(std::shared_ptr<graphics::Framebuffer> framebuffer) {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
        ImGui::ShowDemoWindow();

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
        ImGui::Begin("Scene.");

        ImVec2 viewport_size { ImGui::GetContentRegionAvail() };
        if (_viewport_size.x != viewport_size.x || _viewport_size.y != viewport_size.y) {
            _viewport_size = viewport_size;
            framebuffer->resize(_viewport_size.x, _viewport_size.y);

            for (auto& [_, camera]: _world->filter<Camera>())
                camera.ratio = viewport_size.x / viewport_size.y;
        }

        std::uint64_t texture_id = framebuffer->color_attachment();
        ImGui::Image((void*)texture_id, _viewport_size);

        ImGui::End();
        ImGui::PopStyleVar();

        ImGui::Begin("Objects.");
        for (auto& [entity, transform]: _world->filter<Transform>()) {
            std::string name = entity.has<Id>() ?
                entity.get<Id>().name :
                std::string("Entity: ") + std::to_string(entity.id());
            if (ImGui::Button(name.c_str()))
                _selected_entity = entity;
        }
        if (ImGui::Button("Create Entity.")) {
            auto entity { _world->new_entity() };
            entity.replace<Transform>(0.f, 0.f, 0.f);
        }
        ImGui::End();

        ImGui::Begin("Inspector.");
        if (_selected_entity.has_value()) {
            ImGuiInterpreter::interpret(_selected_entity.value(), _world);

            if (ImGui::TreeNode("Add Component.")) {
                for (auto component: ecs::World::all()) {
                    if (component->has(_world->id(), _selected_entity->id()))
                        continue;

                    if (ImGui::Button(component->name().c_str())) {
                        component->add(_world->id(), _selected_entity->id());
                    }
                }
                ImGui::TreePop();
            }
        }
        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }
}
