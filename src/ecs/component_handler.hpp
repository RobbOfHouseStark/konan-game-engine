#ifndef KGE_ECS_COMPONENT_HANDLER_HPP
#define KGE_ECS_COMPONENT_HANDLER_HPP

#include <cassert>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>

#include "types.hpp"

namespace konan::ecs {
    struct IComponentHandler {
        IComponentHandler();

        virtual void add(WorldId world_id, EntityId entity_id) = 0;
        virtual bool has(WorldId world_id, EntityId entity_id) = 0;
        virtual void clear(WorldId world_id) = 0;
        virtual void del(WorldId world_id, EntityId entity_id) = 0;

        virtual std::size_t size(WorldId world_id) = 0;
        virtual std::string name() = 0;

        void set_one_frame(WorldId world_id);
        bool is_one_frame(WorldId world_id);

    protected:
        std::unordered_set<WorldId> one_frame;
    };

    template <typename Component>
    struct ComponentHandler : public IComponentHandler {
        void add(WorldId world_id, EntityId entity_id) override {
            get(world_id, entity_id);
        }

        Component& get(WorldId world_id, EntityId entity_id) {
            return components_[world_id][entity_id];
        }

        template <typename... Ts>
        Component& replace(WorldId world_id, EntityId entity_id, Ts&& ... params) {
            return components_[world_id].insert_or_assign(entity_id, Component(std::forward<Ts>(params)...))
                .first->second;
        }

        Component& replace(WorldId world_id, EntityId entity_id, Component const& component) {
            return components_[world_id].insert_or_assign(entity_id, component).first->second;
        }

        Component& replace(WorldId world_id, EntityId entity_id, Component&& component) {
            return components_[world_id].insert_or_assign(entity_id, std::move(component)).first->second;
        }

        bool has(WorldId world_id, EntityId entity_id) override {
            return components_[world_id].contains(entity_id);
        }

        void clear(WorldId world_id) override {
            components_.erase(world_id);
        }

        void del(WorldId world_id, EntityId entity_id) override {
            components_[world_id].erase(entity_id);
        }

        std::unordered_map<EntityId, Component>& iter(WorldId world_id) {
            return components_[world_id];
        }

        std::size_t size(WorldId world_id) override {
            return components_[world_id].size();
        }

        std::string name() override {
            return typeid(Component).name();
        }

    private:
        mutable std::unordered_map<WorldId, std::unordered_map<EntityId, Component>> components_;
    };

    template <typename Component>
    struct ComponentHolder {
        inline static ComponentHandler<Component> impl {};
    };
}

#endif  // KGE_ECS_COMPONENT_HANDLER_HPP
