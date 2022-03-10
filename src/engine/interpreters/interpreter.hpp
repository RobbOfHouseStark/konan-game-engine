#ifndef KGE_ENGINE_INTERPRETER_HPP
#define KGE_ENGINE_INTERPRETER_HPP

#include <concepts>
#include <typeindex>
#include <typeinfo>

namespace konan::engine {
    template <typename T>
    concept Interpreter = requires {
        T::get(0);
        T::set(0, nullptr);
        T::has(0);
    };

    template <typename Component, Interpreter Interpreter>
    struct InterpreterHelper {
        explicit InterpreterHelper(void* interpreter) {
            Interpreter::set(typeid(Component).hash_code(), interpreter);
        }
    };
}

#endif  // KGE_ENGINE_INTERPRETER_HPP
