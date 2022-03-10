#ifndef KGE_ENGINE_RENDER_SYSTEM_HPP
#define KGE_ENGINE_RENDER_SYSTEM_HPP

#include <memory>
#include <optional>

#include "ecs/ecs.hpp"
#include "graphics/renderer.hpp"
#include "graphics/window.hpp"

#include "components/camera.hpp"
#include "components/id.hpp"
#include "components/model.hpp"
#include "components/render_data.hpp"
#include "components/script.hpp"
#include "components/transform.hpp"

namespace konan::engine {
    struct RenderSystem : public ecs::IInitSystem,
                          public ecs::IRunSystem {
        explicit RenderSystem(std::shared_ptr<graphics::Renderer> renderer);

        void init() override;
        void run(double dt) override;

    private:
        std::shared_ptr<graphics::Window> window_;
        std::shared_ptr<graphics::Renderer> renderer_;
    };
}

#endif  // KGE_ENGINE_RENDER_SYSTEM_HPP
