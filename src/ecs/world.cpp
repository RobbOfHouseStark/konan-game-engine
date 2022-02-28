#include "world.hpp"
#include "entity.hpp"

namespace konan::ecs {
    World::~World() {
//        for (auto component_handler: components_)
//            component_handler->clear(id_);
    }

    Entity World::new_entity() {
        return { current_entity_id_++, shared_from_this() };
    }

    void World::del(EntityId entity_id) {
        for (auto component_handler: components_)
            component_handler->del(id_, entity_id);
    }

    void World::update() {
        for (auto component: components_) {
            if (component->is_one_frame(id_))
                component->clear(id_);
        }
    }

    WorldId World::id() const {
        return id_;
    }

    void World::register_component(IComponentHandler* component_handler) {
        components_.insert(component_handler);
    }

    std::unordered_set<IComponentHandler*> World::all() {
        return components_;
    }
}
