#include "render_system.hpp"

namespace konan::engine {
    RenderSystem::RenderSystem(std::shared_ptr<graphics::Renderer> renderer,
                               std::shared_ptr<graphics::Framebuffer> framebuffer)
        : _renderer { renderer }, _framebuffer { framebuffer } {}

    void RenderSystem::init() {
        _window = _world->injection<graphics::Window>();
        _window->init_imgui();
    }

    void RenderSystem::run() {
        _framebuffer->bind();
        _window->clear();

        _world->filter<Camera, Transform>(
            [this](auto entity, Camera& camera, Transform& transform) {
                _world->filter<Model, Transform>(
                    [this, &camera, &camera_transform = transform](auto entity, Model& model, Transform& transform) {
                        model.bind();

                        model.shader->load_uniform("v_MVP",
                                                  camera.projection_matrix() *
                                                  camera_transform.view_matrix() *
                                                  transform.model_matrix());

                        _renderer->draw(model.shader, model.texture, model.vertex_array);

                        model.unbind();
                    });
            });

        _framebuffer->unbind();

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
            _framebuffer->resize(_viewport_size.x, _viewport_size.y);

            _world->filter<Camera>(
                [&viewport_size](auto _, Camera& camera) {
                    camera.ratio = viewport_size.x / viewport_size.y;
                });
        }

        std::uint64_t texture_id = _framebuffer->color_attachment();
        ImGui::Image((void*)texture_id, _viewport_size);

        ImGui::End();
        ImGui::PopStyleVar();

        ImGui::Begin("Objects.");
        _world->filter<Id>(
            [this](auto entity, Id& id) {
                if (ImGui::Button(id.name.c_str()))
                    _selected_entity = entity;
            });
        if (ImGui::Button("Create Entity.")) {
            auto entity { _world->new_entity() };
            _world->replace<Id>(entity, "Default", std::string("Entity ") + std::to_string(entity));
            _world->replace<Transform>(entity, 0.f, 0.f, 0.f);
        }
        ImGui::End();

        ImGui::Begin("Inspector.");
        if (_selected_entity.has_value()) {
            ImGuiInterpreter::interpret(_selected_entity.value(), _world);

            if (ImGui::TreeNode("Add Component.")) {
                ImGui::TreePop();
            }
        }
        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        _window->swap_buffers();
    }
}
