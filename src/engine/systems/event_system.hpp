#ifndef KGE_ENGINE_QUIT_SYSTEM_HPP
#define KGE_ENGINE_QUIT_SYSTEM_HPP

#include "ecs/ecs.hpp"
#include "graphics/window.hpp"

#include "events/key.hpp"

namespace konan::engine {
struct EventSystem : public ecs::IInitSystem, public ecs::IRunSystem {
        explicit EventSystem(bool* running);

        void init() override;
        void run(double dt) override;

    private:
        bool* running_;
        std::shared_ptr<graphics::Window> window_;
    };
}

#endif  // KGE_ENGINE_QUIT_SYSTEM_HPP
