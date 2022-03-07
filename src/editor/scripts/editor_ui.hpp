#ifndef KGE_EDITOR_UI_HPP
#define KGE_EDITOR_UI_HPP

#include <memory>
#include <optional>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "ecs/ecs.hpp"
#include "engine/components/camera.hpp"
#include "engine/components/id.hpp"
#include "engine/components/render_data.hpp"
#include "engine/components/script.hpp"
#include "engine/components/transform.hpp"

#include "creator_interpreter.hpp"
#include "imgui_interpreter.hpp"

namespace konan::editor {
    struct EditorUI : public engine::IScriptable {
        void run() override;

    private:
        std::optional<ecs::Entity> selected_entity_;
        ImVec2 viewport_size_;
    };
}

#endif  // KGE_EDITOR_UI_HPP
