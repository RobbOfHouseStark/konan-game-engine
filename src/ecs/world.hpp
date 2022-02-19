#ifndef KGE_ECS_WORLD_HPP
#define KGE_ECS_WORLD_HPP

#include <memory>
#include <typeindex>
#include <typeinfo>
#include <unordered_map>

#include "component_handler.hpp"
#include "types.hpp"

namespace konan::ecs {
    struct World : public std::enable_shared_from_this<World> {
        EntityId new_entity() const;

        template <typename Component>
        Component& get(EntityId entity_id) {
            auto& component { component_handler<Component>() };
            return component.get(entity_id);
        }

        template <typename Component>
        const Component& get(EntityId entity_id) const {
            auto const& component { component_handler<Component>() };
            return component.get(entity_id);
        }

        template <typename Component>
        Component& replace(EntityId entity_id, Component&& new_component) {
            auto& component { component_handler<Component>() };
            return component.replace(entity_id, std::forward<Component>(new_component));
        }

        template <typename Component, typename... Ts>
        Component& replace(EntityId entity_id, Ts&& ... params) {
            auto& component { component_handler<Component>() };
            return component.replace(entity_id, std::forward<Ts>(params)...);
        }

        template <typename Component>
        bool has(EntityId entity_id) const {
            auto const& component { component_handler<Component>() };
            return component.has(entity_id);
        }

        void del(EntityId entity_id);

        template <typename Component>
        void del(EntityId entity_id) {
            auto& component { component_handler<Component>() };
            component.del(entity_id);
        }

        template <typename Component, typename... Components>
        void filter(FilterLambda<Component, Components...> const& lambda) {
            auto& component { component_handler<Component>() };

            if constexpr (sizeof...(Components) == 0) {
                component.filter(lambda);
            } else {
                component.filter(
                    [this, &component, &lambda](EntityId entity_id, Component& iter_component) {
                        if (!(... && component_handler_lazy<Components>().has(entity_id)))
                            return;

                        lambda(entity_id, iter_component,
                               component_handler_lazy<Components>().get_strict(entity_id)...);
                    });
            }
        }

        template <typename Component>
        void one_frame() {
            auto& component { component_handler<Component>() };
            component.set_one_frame();
        }

        void update() {
            for (auto& [_, component]: _components)
                if (component->one_frame())
                    component->clear();
        }

        template <typename Component>
        std::size_t size() const {
            auto const& component { component_handler<Component>() };
            return component.size();
        }

    template <typename Injection, typename... Ts>
    std::shared_ptr<Injection> inject(Ts&& ... params) {
        return inject(std::make_shared<Injection>(std::forward<Ts>(params)...));
    }

    template <typename Injection>
    std::shared_ptr<Injection> inject(std::shared_ptr<Injection> injection) {
        _injections.emplace(typeid(Injection).hash_code(), injection);
        return injection;
    }

    template <typename Injection>
    std::shared_ptr<Injection> injection() {
        ComponentId const component_id { typeid(Injection).hash_code() };
        auto injection_iterator { _injections.find(component_id) };
        if (injection_iterator == _injections.end())
            assert(false);
        return std::static_pointer_cast<Injection>(injection_iterator->second);
    }

    private:
        template <typename Component>
        ComponentHandler<Component>& component_handler() const {
            ComponentId const component_id { typeid(Component).hash_code() };

            if (!_components.contains(component_id)) {
                auto component { std::make_shared<ComponentHandler<Component>>() };
                _components.emplace(component_id, component);
                return *component.get();
            }

            return *std::dynamic_pointer_cast<ComponentHandler<Component>>(_components[component_id]).get();
        }

        template <typename Component>
        ComponentHandler<Component>& component_handler_lazy() {
            ComponentId const component_id { typeid(Component).hash_code() };
            return *std::dynamic_pointer_cast<ComponentHandler<Component>>(_components[component_id]).get();
        }

    private:
        mutable EntityId _next_entity_id {};
        mutable std::unordered_map<ComponentId, std::shared_ptr<IComponentHandler>> _components;
        std::unordered_map<InjectionId, std::shared_ptr<void>> _injections;
    };
}

#endif  // KGE_ECS_WORLD_HPP
