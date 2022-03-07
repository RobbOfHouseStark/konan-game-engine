#ifndef KGE_ENGINE_CREATOR_INTERPRETER_HPP
#define KGE_ENGINE_CREATOR_INTERPRETER_HPP

#include <typeindex>
#include <typeinfo>
#include <unordered_map>
#include <utility>

#include "ecs/ecs.hpp"

namespace konan::engine {
    struct ICreatorInterpreter {
        static bool has(std::size_t component_id) {
            return factories_.contains(component_id);
        }

        static void* get(std::size_t component_id) {
            auto factories_iterator { factories_.find(component_id) };
            assert(factories_iterator != factories_.end());
            return factories_iterator->second;
        }

        static void set(std::size_t id, void* factory) {
            factories_.insert_or_assign(id, factory);
        }

    private:
        inline static std::unordered_map<std::size_t, void*> factories_ {};
    };

    template <typename Component>
    struct CreatorHelper {
        explicit CreatorHelper(void* factory) {
            ICreatorInterpreter::set(typeid(Component).hash_code(), factory);
        }
    };

    template <typename Component, Component(*Factory)()>
    struct CreatorInterpreter : public ICreatorInterpreter {
        static Component interpret(ecs::IComponentHandler* component) {
            return Factory();
        }

    private:
        inline static CreatorHelper<Component> helper_ { Factory };
    };
}

#endif  // KGE_ENGINE_CREATOR_INTERPRETER_HPP
