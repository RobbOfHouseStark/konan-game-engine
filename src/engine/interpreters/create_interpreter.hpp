#ifndef KGE_ENGINE_CREATOR_INTERPRETER_HPP
#define KGE_ENGINE_CREATOR_INTERPRETER_HPP

#include <cassert>
#include <unordered_map>

#include "interpreter.hpp"

namespace konan::engine {
    struct ICreateInterpreter {
        static bool has(std::size_t component_id) {
            return interpreters_.contains(component_id);
        }

        static void* get(std::size_t component_id) {
            auto factories_iterator { interpreters_.find(component_id) };
            assert(factories_iterator != interpreters_.end());
            return factories_iterator->second;
        }

        static void set(std::size_t id, void* factory) {
            interpreters_.insert_or_assign(id, factory);
        }

    private:
        inline static std::unordered_map<std::size_t, void*> interpreters_ {};
    };

    template <typename Component, Component(*Interpreter)()>
    class CreateInterpreter {
        inline static InterpreterHelper<Component, ICreateInterpreter> helper_ { Interpreter };
    };
}

#endif  // KGE_ENGINE_CREATOR_INTERPRETER_HPP
