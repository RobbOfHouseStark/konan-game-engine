#ifndef KGE_ENGINE_IMGUIINTERPRETER_HPP
#define KGE_ENGINE_IMGUIINTERPRETER_HPP

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "id.hpp"
#include "transform.hpp"
#include "world.hpp"

namespace konan::engine {
    struct ImGuiInterpreter {
        static void interpret(ecs::EntityId entity, std::shared_ptr<ecs::World> world) {
            if (world->has<Id>(entity)) {
                if (ImGui::TreeNode("Id.")) {
                    auto& component { world->get<Id>(entity) };
                    ImGui::InputText("Tag.", (char*)component.tag.c_str(), 50);
                    ImGui::InputText("Name.", (char*)component.name.c_str(), 50);
                    ImGui::TreePop();
                }
            }
            if (world->has<Transform>(entity)) {
                if (ImGui::TreeNode("Transform.")) {
                    auto& component { world->get<Transform>(entity) };
                    ImGui::DragFloat3("Position.", &(component.position[0]));
                    ImGui::DragFloat3("Rotation.", &(component.rotation[0]), 2.f);
                    ImGui::DragFloat3("Scale.", &(component.scale[0]), .1f, 100.f, .001f, "%.3f", 0);
                    ImGui::TreePop();
                }
            }
            if (world->has<Camera>(entity)) {
                auto& component { world->get<Camera>(entity) };
                if (ImGui::TreeNode("Camera.")) {
                    ImGui::DragFloat("Fov.", &(component.fov));
                    ImGui::DragFloat("Ratio.", &(component.ratio), 0.01f, 0.f, 3.f);
                    ImGui::DragFloat("Near Clipping Plane.", &(component.near_clipping_plane));
                    ImGui::DragFloat("Far Clipping Plane..", &(component.far_clipping_plane));
                    ImGui::TreePop();
                }
            }
        }
    };
}

#endif  // KGE_ENGINE_IMGUIINTERPRETER_HPP
