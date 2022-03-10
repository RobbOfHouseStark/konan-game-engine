#include "systems.hpp"

namespace konan::ecs {
    void ISystem::owners(std::shared_ptr<World> owner_world, Systems* owner_systems) {
        world = owner_world;
        systems = owner_systems;
    }
}
