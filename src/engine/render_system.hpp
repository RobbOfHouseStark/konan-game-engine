#ifndef KGE_ENGINE_RENDER_SYSTEM_HPP
#define KGE_ENGINE_RENDER_SYSTEM_HPP

#include "systems.hpp"
#include "window.hpp"

namespace konan::engine {
    struct RenderSystem : public ecs::IRunSystem {
        void run() override;
    };
}

#endif  // KGE_ENGINE_RENDER_SYSTEM_HPP
