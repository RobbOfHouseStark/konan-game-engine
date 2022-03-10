#ifndef KGE_ENGINE_INPUT_SYSTEM_HPP
#define KGE_ENGINE_INPUT_SYSTEM_HPP

#include <optional>

#include "ecs/ecs.hpp"
#include "graphics/window.hpp"

#include "events/button.hpp"
#include "events/key.hpp"
#include "events/mouse_move.hpp"

namespace konan::engine {
    struct InputSystem : public ecs::IInitSystem,
                         public ecs::IRunSystem {
        void init() override;
        void run(double dt) override;

    private:
        std::shared_ptr<graphics::Window> window_;
        double previous_x_ {}, previous_y_ {};
    };
}

#endif  // KGE_ENGINE_INPUT_SYSTEM_HPP
