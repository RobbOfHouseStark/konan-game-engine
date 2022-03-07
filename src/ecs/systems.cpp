#include "systems.hpp"

namespace konan::ecs {
    void ISystem::set_world(std::shared_ptr<World> owner) {
        world = owner;
    }
}
