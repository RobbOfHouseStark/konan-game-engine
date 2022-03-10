#include "editor_ui.hpp"

namespace konan::editor {
    void EditorUI::init() {
        scene_world_ = world->injection<ecs::World>();
    }

    void EditorUI::run(double dt) {
        for (auto& [_, camera, render_data]: world->filter<engine::Camera, engine::RenderData>()) {
            ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
            ImGui::ShowDemoWindow();

            ImGui::Begin("Start window.");
            if (ImGui::Button("|>")) {
                auto entity { world->new_entity() };
                entity.get<Start>();
            }
            ImGui::SameLine();
            if (ImGui::Button("||")) {
                auto entity { world->new_entity() };
                entity.get<End>();
            }
            ImGui::End();

            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
            ImGui::Begin("Editor.");
            ImVec2 viewport_size { ImGui::GetContentRegionAvail() };
            if (viewport_size_.x != viewport_size.x || viewport_size_.y != viewport_size.y) {
                viewport_size_ = viewport_size;
                render_data.framebuffer->resize(viewport_size_.x, viewport_size_.y);
                camera.ratio = viewport_size.x / viewport_size.y;
            }
            std::uint64_t texture_id { render_data.framebuffer->color_attachment() };
            ImGui::Image((void*) texture_id, viewport_size_);
            ImGui::End();

            // ImGui::Begin("Scene.");
            // for (auto& [s, scene_camera, scene_render_data]:
            //         scene_world_->filter<engine::Camera, engine::RenderData>()) {
            //     scene_render_data.framebuffer->resize(viewport_size_.x, viewport_size_.y);
            //     scene_camera = camera;
            //     std::uint64_t scene_texture_id { scene_render_data.framebuffer->color_attachment() };
            //     ImGui::Image((void*) scene_texture_id, viewport_size_);
            // }
            // ImGui::End();
            ImGui::PopStyleVar();

            ImGui::Begin("Tools.");
            for (auto& [entity, transform]: world->filter<engine::Transform>()) {
                std::string name = entity.has<engine::Id>() ?
                                                             entity.get<engine::Id>().name :
                                                             std::string("Entity: ") + std::to_string(entity.id());
                if (ImGui::Button(name.c_str()))
                    selected_entity_ = entity;
            }
            ImGui::End();

            ImGui::Begin("Objects.");
            for (auto& [entity, transform]: scene_world_->filter<engine::Transform>()) {
                std::string name = entity.has<engine::Id>() ?
                                   entity.get<engine::Id>().name :
                                   std::string("Entity: ") + std::to_string(entity.id());
                if (ImGui::Button(name.c_str()))
                    selected_entity_ = entity;
            }
            if (ImGui::Button("Create Entity.")) {
                auto entity { scene_world_->new_entity() };
                entity.replace<engine::Transform>(0.f, 0.f, 0.f);
            }
            ImGui::End();

            ImGui::Begin("Inspector.");
            if (selected_entity_.has_value()) {
                for (auto component: ecs::World::all()) {
                    if (!component->has(selected_entity_->world()->id(), selected_entity_->id()))
                        continue;

                    if (ImGui::CollapsingHeader(component->name().c_str())) {
                        if (engine::IImGuiInterpreter::has(component->id())) {
                            component->get(selected_entity_->world()->id(), selected_entity_->id(),
                                           engine::IImGuiInterpreter::get(component->id()));
                        }
                    }
                }

                if (ImGui::Button("Add component."))
                    ImGui::OpenPopup("add_component_popup");
                if (ImGui::BeginPopup("add_component_popup")) {
                    for (auto component: ecs::World::all()) {
                        if (component->has(selected_entity_->world()->id(), selected_entity_->id()) ||
                            component->is_one_frame())
                            continue;

                        if (!ImGui::Button(component->name().c_str()))
                            continue;

                        if (component->default_constructable()) {
                            component->add(selected_entity_->world()->id(), selected_entity_->id());
                        } else if (engine::ICreateInterpreter::has(component->id())) {
                           component->add(selected_entity_->world()->id(), selected_entity_->id(),
                                          engine::ICreateInterpreter::get(component->id()));
                        }
                    }
                    ImGui::EndPopup();
                }
            }
            ImGui::End();
        }
    }
}
