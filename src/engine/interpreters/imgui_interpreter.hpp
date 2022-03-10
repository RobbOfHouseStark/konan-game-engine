#ifndef KGE_ENGINE_IMGUIINTERPRETER_HPP
#define KGE_ENGINE_IMGUIINTERPRETER_HPP

#include <unordered_map>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "interpreter.hpp"

namespace konan::engine {
    struct IImGuiInterpreter {
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

    template <typename Component, void(*Interpreter)(Component&)>
    class ImGuiInterpreter {
        inline static InterpreterHelper<Component, IImGuiInterpreter> helper_ { Interpreter };
    };
}

#endif  // KGE_ENGINE_IMGUIINTERPRETER_HPP
