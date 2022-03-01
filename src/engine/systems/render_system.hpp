#ifndef KGE_ENGINE_RENDER_SYSTEM_HPP
#define KGE_ENGINE_RENDER_SYSTEM_HPP

#include <memory>
#include <optional>

#include "camera.hpp"
#include "ecs.hpp"
#include "id.hpp"
#include "model.hpp"
#include "renderer.hpp"
#include "render_data.hpp"
#include "script.hpp"
#include "transform.hpp"
#include "window.hpp"

namespace konan::engine {
    struct RenderSystem : public ecs::IInitSystem,
                          public ecs::IRunSystem {
        explicit RenderSystem(std::shared_ptr<graphics::Renderer> renderer);

        void init() override;
        void run() override;

    private:
        std::shared_ptr<graphics::Window> _window;
        std::shared_ptr<graphics::Renderer> _renderer;

        std::optional<ecs::Entity> _selected_entity;
    };
}

#endif  // KGE_ENGINE_RENDER_SYSTEM_HPP
