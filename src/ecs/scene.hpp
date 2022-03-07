#ifndef KGE_ECS_SCENE_HPP
#define KGE_ECS_SCENE_HPP

#include "systems.hpp"
#include "world.hpp"

namespace konan::ecs {
    struct Scene {
        explicit Scene(bool* running);

        void init();
        void run(double dt);
        void destroy();

    protected:
        bool* running {};

        std::shared_ptr<World> world;
        std::shared_ptr<Systems> systems;
    };
}

#endif  // KGE_ECS_SCENE_HPP
