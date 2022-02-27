#ifndef KGE_ENGINE_INPUT_SYSTEM_HPP
#define KGE_ENGINE_INPUT_SYSTEM_HPP

#include <optional>

#include "button.hpp"
#include "ecs.hpp"
#include "key.hpp"
#include "mouse_move.hpp"
#include "window.hpp"

namespace konan::engine {
    struct InputSystem : public ecs::IInitSystem,
                         public ecs::IRunSystem {
        void init() override;
        void run() override;

    private:
        std::shared_ptr<graphics::Window> _window;
        double _previous_x {}, _previous_y {};
    };
}

#endif  // KGE_ENGINE_INPUT_SYSTEM_HPP
