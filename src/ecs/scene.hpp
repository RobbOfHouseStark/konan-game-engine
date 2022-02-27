#ifndef KGE_ECS_SCENE_HPP
#define KGE_ECS_SCENE_HPP

#include "systems.hpp"
#include "world.hpp"

namespace konan::ecs {
    struct Scene {
        void run();

    protected:
        bool _running { true };

        std::shared_ptr<World> _world { std::make_shared<World>() };
        std::shared_ptr<Systems> _systems { std::make_shared<Systems>(_world) };
    };
}

#endif  // KGE_ECS_SCENE_HPP
