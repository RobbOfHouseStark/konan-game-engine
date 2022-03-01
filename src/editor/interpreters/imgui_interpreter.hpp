#ifndef KGE_ENGINE_IMGUIINTERPRETER_HPP
#define KGE_ENGINE_IMGUIINTERPRETER_HPP

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "id.hpp"
#include "model.hpp"
#include "transform.hpp"
#include "world.hpp"

namespace konan::editor {
    struct ImGuiInterpreter {
        static void interpret(ecs::Entity entity) {
            if (entity.has<engine::Id>()) {
                if (ImGui::CollapsingHeader("Id.")) {
                    auto& component { entity.get<engine::Id>() };
                    ImGui::InputText("Tag.", (char*)component.tag.c_str(), 50);
                    ImGui::InputText("Name.", (char*)component.name.c_str(), 50);
                }
            }
            if (entity.has<engine::Transform>()) {
                if (ImGui::CollapsingHeader("Transform.")) {
                    auto& component { entity.get<engine::Transform>() };
                    ImGui::DragFloat3("Position.", &(component.position[0]));
                    ImGui::DragFloat3("Rotation.", &(component.rotation[0]), 2.f);
                    ImGui::DragFloat3("Scale.", &(component.scale[0]), .1f, 100.f, .001f, "%.3f", 0);
                }
            }
            if (entity.has<engine::Camera>()) {
                auto& component { entity.get<engine::Camera>() };
                if (ImGui::CollapsingHeader("Camera.")) {
                    ImGui::DragFloat("Fov.", &(component.fov));
                    ImGui::DragFloat("Ratio.", &(component.ratio), 0.01f, 0.f, 3.f);
                    ImGui::DragFloat("Near Clipping Plane.", &(component.near_clipping_plane));
                    ImGui::DragFloat("Far Clipping Plane..", &(component.far_clipping_plane));
                }
            }
            if (entity.has<engine::Model>()) {
                auto& component { entity.get<engine::Model>() };
                if (ImGui::CollapsingHeader("Model.")) {
                    ImGui::Text("Model data.");
                }
            }
        }
    };
}

#endif  // KGE_ENGINE_IMGUIINTERPRETER_HPP
