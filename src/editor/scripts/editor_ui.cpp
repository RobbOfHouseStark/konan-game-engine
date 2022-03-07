#include "editor_ui.hpp"

namespace konan::editor {
    void EditorUI::run() {
        for (auto& [_, camera, render_data]: world->filter<engine::Camera, engine::RenderData>()) {
            ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
            ImGui::ShowDemoWindow();

            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
            ImGui::Begin("Scene.");

            ImVec2 viewport_size { ImGui::GetContentRegionAvail() };
            if (viewport_size_.x != viewport_size.x || viewport_size_.y != viewport_size.y) {
                viewport_size_ = viewport_size;
                render_data.framebuffer->resize(viewport_size_.x, viewport_size_.y);

                camera.ratio = viewport_size.x / viewport_size.y;
            }

            std::uint64_t texture_id = render_data.framebuffer->color_attachment();
            ImGui::Image((void*) texture_id, viewport_size_);

            ImGui::End();
            ImGui::PopStyleVar();

            ImGui::Begin("Objects.");
            for (auto&[entity, transform]: world->filter<engine::Transform>()) {
                std::string name = entity.has<engine::Id>() ?
                                   entity.get<engine::Id>().name :
                                   std::string("Entity: ") + std::to_string(entity.id());
                if (ImGui::Button(name.c_str()))
                    selected_entity_ = entity;
            }
            if (ImGui::Button("Create Entity.")) {
                auto entity { world->new_entity() };
                entity.replace<engine::Transform>(0.f, 0.f, 0.f);
            }
            ImGui::End();

            ImGui::Begin("Inspector.");
            if (selected_entity_.has_value()) {
                ImGuiInterpreter::interpret(selected_entity_.value());

                if (ImGui::Button("Add component."))
                    ImGui::OpenPopup("add_component_popup");
                if (ImGui::BeginPopup("add_component_popup")) {
                    for (auto component: ecs::World::all()) {
                        if (component->has(world->id(), selected_entity_->id()))
                            continue;

                        if (!ImGui::Button(component->name().c_str()))
                            continue;

                        if (component->default_constructable()) {
                            component->add(world->id(), selected_entity_->id());
                        } else if (engine::ICreatorInterpreter::has(component->id())) {
                            engine::ICreatorInterpreter::get(component->id());
                        }
                    }
                    ImGui::EndPopup();
                }
            }
            ImGui::End();
        }
    }
}
