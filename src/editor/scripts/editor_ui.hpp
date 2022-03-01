#ifndef KGE_EDITOR_UI_HPP
#define KGE_EDITOR_UI_HPP

#include <memory>
#include <optional>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "camera.hpp"
#include "ecs.hpp"
#include "id.hpp"
#include "imgui_interpreter.hpp"
#include "render_data.hpp"
#include "script.hpp"
#include "transform.hpp"

namespace konan::editor {
    struct EditorUI : public engine::IScriptable {
        void run() override;

    private:
        std::optional<ecs::Entity> _selected_entity;
        ImVec2 _viewport_size;
    };
}

#endif  // KGE_EDITOR_UI_HPP
