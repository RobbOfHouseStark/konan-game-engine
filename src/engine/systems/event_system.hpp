#ifndef KGE_ENGINE_QUIT_SYSTEM_HPP
#define KGE_ENGINE_QUIT_SYSTEM_HPP

#include "systems.hpp"
#include "window.hpp"

namespace konan::engine {
    struct EventSystem : public ecs::IRunSystem {
        explicit EventSystem(bool* running);
        void run() override;

    private:
        bool* _running;
        std::shared_ptr<graphics::Window> _window;
    };
}

#endif  // KGE_ENGINE_QUIT_SYSTEM_HPP
