#ifndef KGE_ECS_SCENE_HPP
#define KGE_ECS_SCENE_HPP

#include <utility>

#include "entity.hpp"
#include "systems.hpp"
#include "world.hpp"

namespace konan::ecs {
    struct Scene {
        explicit Scene();

        virtual void init();
        virtual void run(double dt);
        virtual void destroy();

        std::shared_ptr<World> get_world();
        std::shared_ptr<Systems> get_systems();

    protected:
        std::shared_ptr<World> world;
        std::shared_ptr<Systems> systems;
    };
}

#endif  // KGE_ECS_SCENE_HPP
