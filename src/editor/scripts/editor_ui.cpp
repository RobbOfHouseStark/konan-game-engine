#include "editor_ui.hpp"

namespace konan::editor {
    void EditorUI::run() {
        for (auto& [_, camera, render_data]: world->filter<engine::Camera, engine::RenderData>()) {
            ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
            ImGui::ShowDemoWindow();

            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
            ImGui::Begin("Scene.");

            ImVec2 viewport_size { ImGui::GetContentRegionAvail() };
            if (_viewport_size.x != viewport_size.x || _viewport_size.y != viewport_size.y) {
                _viewport_size = viewport_size;
                render_data.framebuffer->resize(_viewport_size.x, _viewport_size.y);

                camera.ratio = viewport_size.x / viewport_size.y;
            }

            std::uint64_t texture_id = render_data.framebuffer->color_attachment();
            ImGui::Image((void*) texture_id, _viewport_size);

            ImGui::End();
            ImGui::PopStyleVar();

            ImGui::Begin("Objects.");
            for (auto& [entity, transform]: world->filter<engine::Transform>()) {
                std::string name = entity.has<engine::Id>() ?
                                   entity.get<engine::Id>().name :
                                   std::string("Entity: ") + std::to_string(entity.id());
                if (ImGui::Button(name.c_str()))
                    _selected_entity = entity;
            }
            if (ImGui::Button("Create Entity.")) {
                auto entity { world->new_entity() };
                entity.replace<engine::Transform>(0.f, 0.f, 0.f);
            }
            ImGui::End();

            ImGui::Begin("Inspector.");
            if (_selected_entity.has_value()) {
                ImGuiInterpreter::interpret(_selected_entity.value());

                if (ImGui::Button("Add component."))
                    ImGui::OpenPopup("add_component_popup");
                if (ImGui::BeginPopup("add_component_popup")) {
                    for (auto component: ecs::World::all()) {
                        if (component->has(world->id(), _selected_entity->id()))
                            continue;

                        if (ImGui::Button(component->name().c_str()))
                            component->add(world->id(), _selected_entity->id());
                    }
                    ImGui::EndPopup();
                }
            }
            ImGui::End();
        }
    }
}
