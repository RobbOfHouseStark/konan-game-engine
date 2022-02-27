#ifndef KGE_ENGINE_RENDER_SYSTEM_HPP
#define KGE_ENGINE_RENDER_SYSTEM_HPP

#include <memory>
#include <optional>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "camera.hpp"
#include "ecs.hpp"
#include "framebuffer.hpp"
#include "id.hpp"
#include "imgui_interpreter.hpp"
#include "model.hpp"
#include "renderer.hpp"
#include "transform.hpp"
#include "window.hpp"

namespace konan::engine {
    struct RenderSystem : public ecs::IInitSystem,
                          public ecs::IRunSystem {
        RenderSystem(std::shared_ptr<graphics::Renderer> renderer);

        void init() override;
        void run() override;

    private:
        void render_ui(std::shared_ptr<graphics::Framebuffer> framebuffer);

    private:
        std::shared_ptr<graphics::Window> _window;
        std::shared_ptr<graphics::Renderer> _renderer;
        ImVec2 _viewport_size {};

        std::optional<ecs::Entity> _selected_entity;
    };
}

#endif  // KGE_ENGINE_RENDER_SYSTEM_HPP
