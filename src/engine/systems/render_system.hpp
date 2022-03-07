#ifndef KGE_ENGINE_RENDER_SYSTEM_HPP
#define KGE_ENGINE_RENDER_SYSTEM_HPP

#include <memory>
#include <optional>

#include "ecs/ecs.hpp"
#include "graphics/renderer.hpp"
#include "graphics/window.hpp"

#include "camera.hpp"
#include "id.hpp"
#include "model.hpp"
#include "render_data.hpp"
#include "script.hpp"
#include "transform.hpp"

namespace konan::engine {
    struct RenderSystem : public ecs::IInitSystem,
                          public ecs::IRunSystem {
        explicit RenderSystem(std::shared_ptr<graphics::Renderer> renderer);

        void init() override;
        void run(double dt) override;

    private:
        std::shared_ptr<graphics::Window> window_;
        std::shared_ptr<graphics::Renderer> renderer_;

        std::optional<ecs::Entity> selected_entity_;
    };
}

#endif  // KGE_ENGINE_RENDER_SYSTEM_HPP
