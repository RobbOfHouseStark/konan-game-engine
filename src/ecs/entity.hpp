#ifndef KGE_ECS_ENTITY_HPP
#define KGE_ECS_ENTITY_HPP

#include "types.hpp"
#include "world.hpp"

namespace konan::ecs {
    struct Entity {
        Entity(EntityId id, std::shared_ptr<World> world);

        template <typename Component>
        Component& get() {
            return world_->get<Component>(id_);
        }

        template <typename Component>
        Component& get() const {
            return world_->get<Component>(id_);
        }

        template <typename Component, typename... Ts>
        Component& replace(Ts&& ... params) {
            return world_->replace<Component>(id_, std::forward<Ts>(params)...);
        }

        template <typename Component>
        Component& replace(Component&& component) {
            return world_->replace<Component>(id_, std::forward<component>(component));
        }

        template <typename Component>
        bool has() const {
            return world_->has<Component>(id_);
        }

        template <typename Component>
        void del() {
            world_->del<Component>(id_);
        }

        void del();

        EntityId id() const;

        std::shared_ptr<World> world();
        std::shared_ptr<World const> world() const;

    private:
        EntityId id_;
        std::shared_ptr<World> world_;
    };
}

#endif  // KGE_ECS_ENTITY_HPP
