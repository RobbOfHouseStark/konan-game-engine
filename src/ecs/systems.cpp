#include "systems.hpp"

namespace konan::ecs {
    void ISystem::world(std::shared_ptr<World> world) {
        _world = world;
    }
}
