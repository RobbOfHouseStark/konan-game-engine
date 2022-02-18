#ifndef KGE_ECS_COMPONENT_HANDLER_HPP
#define KGE_ECS_COMPONENT_HANDLER_HPP

#include <cassert>
#include <unordered_map>

#include "types.hpp"

namespace konan::ecs {
    struct IComponentHandler {
        virtual ~IComponentHandler() = default;

        virtual bool has(EntityId entity_id) const = 0;
        virtual void del(EntityId entity_id) = 0;
        virtual void clear() = 0;
        virtual std::size_t size() const = 0;

        void set_one_frame() {
            _one_frame = true;
        }

        bool one_frame() {
            return _one_frame;
        }

    protected:
        bool _one_frame {};
    };

    template <typename Component>
    struct ComponentHandler : public IComponentHandler {
        Component& get(EntityId entity_id) {
            if constexpr (std::is_default_constructible_v<Component>) {
                return _components[entity_id];
            } else {
                auto component_iterator { _components.find(entity_id) };
                if (component_iterator == _components.end())
                    assert(false);
                return component_iterator->second;
            }
        }

        const Component& get(EntityId entity_id) const {
            auto component_iterator { _components.find(entity_id) };
            if (component_iterator == _components.end())
                assert(false);
            return component_iterator->second;
        }

        Component& get_strict(EntityId entity_id) {
            return _components.find(entity_id)->second;
        }

        Component& replace(EntityId entity_id, Component const& component) {
            return _components.insert_or_assign(entity_id, component).first->second;
        }

        Component& replace(EntityId entity_id, Component&& component) {
            return _components.insert_or_assign(entity_id, std::move(component)).first->second;
        }

        template <typename... Ts>
        Component& replace(EntityId entity_id, Ts&& ... params) {
            return _components.emplace(std::piecewise_construct,
                                       std::forward_as_tuple(entity_id),
                                       std::forward_as_tuple(std::forward<Ts>(params)...)).first->second;
        }

        bool has(EntityId entity_id) const override {
            return _components.contains(entity_id);
        }

        void del(EntityId entity_id) override {
            _components.erase(entity_id);
        }

        void filter(FilterLambda<Component> const& lambda) {
            for (auto& [entity_id, component]: _components) {
                lambda(entity_id, component);
            }
        }

        void clear() override {
            _components.clear();
        }

        std::size_t size() const override {
            return _components.size();
        }

    private:
        std::unordered_map<EntityId, Component> _components;
    };
}

#endif  // KGE_ECS_COMPONENT_HANDLER_HPP
