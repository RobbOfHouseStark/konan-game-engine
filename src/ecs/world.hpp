#ifndef KGE_ECS_WORLD_HPP
#define KGE_ECS_WORLD_HPP

#include <typeinfo>
#include <typeindex>
#include <tuple>
#include <unordered_set>

#include "component_handler.hpp"
#include "component_iterable.hpp"
#include "types.hpp"

namespace konan::ecs {
    struct World : public std::enable_shared_from_this<World> {
        ~World();

        Entity new_entity();

        template <typename Component>
        Component& get(EntityId entity_id) {
            return ComponentHolder<Component>::impl.get(id_, entity_id);
        }

        template <typename Component>
        Component const& get(EntityId entity_id) const {
            return ComponentHolder<Component>::impl.get(id_, entity_id);
        }

        template <typename Component, typename... Ts>
        Component& replace(EntityId entity_id, Ts&& ... params) {
            return ComponentHolder<Component>::impl.replace(id_, entity_id, std::forward<Ts>(params)...);
        }

        template <typename Component>
        Component& replace(EntityId entity_id, Component&& component) {
            return ComponentHolder<Component>::impl.replace(id_, entity_id, std::forward<Component>(component));
        }

        template <typename Component>
        bool has(EntityId entity_id) const {
            return ComponentHolder<Component>::impl.has(id_, entity_id);
        }

        template <typename Component>
        void del(EntityId entity_id) {
            ComponentHolder<Component>::impl.del(id_, entity_id);
        }

        void del(EntityId entity_id);

        template <typename Component, typename... Components>
        decltype(auto) filter() {
            if constexpr (sizeof...(Components) == 0) {
                return ComponentIterable<std::pair<Entity, Component&>>(iter<Component>());
            } else {
                return ComponentIterable<std::tuple<Entity, Component&, Components&...>>(
                    each<Component, Components...>()
                );
            }
        }

        template <typename Component, typename... Components>
        decltype(auto) filter() const {
            if constexpr (sizeof...(Components) == 0) {
                return ComponentIterable<std::pair<Entity, Component&>>(iter<Component>());
            } else {
                return ComponentIterable<std::tuple<Entity, Component&, Components&...>>(
                    each<Component, Components...>()
                );
            }
        }

        template <typename Injection, typename... Ts>
        void inject(Ts&& ... params) {
            _injections.emplace(typeid(Injection).hash_code(), std::make_shared<Injection>(std::forward<Ts>(params)...));
        }

        template <typename Injection>
        std::shared_ptr<Injection> inject(std::shared_ptr<Injection> injection) {
            _injections.emplace(typeid(Injection).hash_code(), injection);
            return injection;
        }

        template <typename Injection>
        std::shared_ptr<Injection> injection() {
            auto injection_iterator { _injections.find(typeid(Injection).hash_code()) };
            assert(injection_iterator != _injections.end());
            return std::static_pointer_cast<Injection>(injection_iterator->second);
        }

        template <typename Component>
        void one_frame() {
            ComponentHolder<Component>::impl.set_one_frame(id_);
        }

        void update();

        template <typename Component>
        std::size_t size() const {
            return ComponentHolder<Component>::impl.size(id_);
        }

        WorldId id() const;

    public:
        static void register_component(IComponentHandler* component_handler);
        static std::unordered_set<IComponentHandler*> all();

    private:
        template <typename Component, typename... Components>
        auto each() -> ComponentGenerator<std::tuple<Entity, Component&, Components&...>> {
            for (auto& [entity_id, component]: ComponentHolder<Component>::impl.iter(id_)) {
                if ((... && ComponentHolder<Components>::impl.has(id_, entity_id))) {
                    std::tuple<Entity, Component&, Components&...> t {
                        { entity_id, shared_from_this() }, component,
                        ComponentHolder<Components>::impl.get(id_, entity_id)... };
                    co_yield t;
                }
            }

            co_return;
        }

        template <typename Component, typename... Components>
        auto each() const -> ComponentGenerator<std::tuple<Entity, Component const&, Components const&...>> {
            for (auto& [entity_id, component]: ComponentHolder<Component>::impl.iter(id_)) {
                if ((... && ComponentHolder<Components>::impl.has(id_, entity_id))) {
                    std::tuple<Entity, Component const&, Components const&...> tuple {
                        { entity_id, shared_from_this() }, component,
                        ComponentHolder<Components>::impl.get_without_check(id_, entity_id)... };
                    co_yield tuple;
                }
            }

            co_return;
        }

        template <typename Component>
        auto iter() -> ComponentGenerator<std::pair<Entity, Component&>> {
            for (auto& [entity_id, component]: ComponentHolder<Component>::impl.iter(id_)) {
                std::pair<Entity, Component&> pair { { entity_id, shared_from_this() }, component };
                co_yield pair;
            }

            co_return;
        }

        template <typename Component>
        auto iter() const -> ComponentGenerator<std::pair<Entity, Component const&>> {
            for (auto& [entity_id, component]: ComponentHolder<Component>::impl.iter(id_)) {
                auto pair { std::make_pair<Entity, Component const&>({ entity_id, shared_from_this() }, component) };
                co_yield pair;
            }

            co_return;
        }

    private:
        WorldId id_ { current_world_id_++ };
        EntityId current_entity_id_ {};

        std::unordered_map<std::size_t, std::shared_ptr<void>> _injections;

        inline static WorldId current_world_id_ {};
        inline static std::unordered_set<IComponentHandler*> components_;
    };
}

#endif  // KGE_ECS_WORLD_HPP
