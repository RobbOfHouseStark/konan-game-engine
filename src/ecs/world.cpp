#include "world.hpp"

namespace konan::ecs {
    EntityId World::new_entity() const {
        return _next_entity_id++;
    }
    void World::del(EntityId entity_id) {
        for (auto [_, component_interface]: _components) {
            component_interface->del(entity_id);
        }
    }
}
