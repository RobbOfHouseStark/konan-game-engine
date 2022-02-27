#include "entity.hpp"

namespace konan::ecs {
    Entity::Entity(EntityId id, std::shared_ptr<World> world)
        : id_ { id }, world_ { world } {}

    void Entity::del() {
        world_->del(id_);
    }

    EntityId Entity::id() const {
        return id_;
    }

    std::shared_ptr<World> Entity::world() {
        return world_;
    }

    std::shared_ptr<World const> Entity::world() const {
        return std::const_pointer_cast<World const>(world_);
    }
}
