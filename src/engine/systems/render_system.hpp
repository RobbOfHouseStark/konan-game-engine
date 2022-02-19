#ifndef KGE_ENGINE_RENDER_SYSTEM_HPP
#define KGE_ENGINE_RENDER_SYSTEM_HPP

#include "camera.hpp"
#include "gl_model.hpp"
#include "systems.hpp"
#include "transform.hpp"
#include "window.hpp"

namespace konan::engine {
    struct RenderSystem : public ecs::IInitSystem,
                          public ecs::IRunSystem {
        void init() override;
        void run() override;

    private:
        std::shared_ptr<graphics::Window> _window;
    };
}

#endif  // KGE_ENGINE_RENDER_SYSTEM_HPP
