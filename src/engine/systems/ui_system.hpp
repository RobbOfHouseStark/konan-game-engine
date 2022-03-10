#ifndef KGE_ENGINE_UI_SYSTEM_HPP
#define KGE_ENGINE_UI_SYSTEM_HPP

#include "ecs/ecs.hpp"
#include "components/camera.hpp"
#include "components/script.hpp"
#include "graphics/window.hpp"

namespace konan::engine {
    struct UISystem : public ecs::IInitSystem,
                      public ecs::IRunSystem {
        void init() override;
        void run(double dt) override;

    private:
        std::shared_ptr<graphics::Window> window_;
    };
}

#endif  // KGE_ENGINE_UI_SYSTEM_HPP
