#include "script_system.hpp"

namespace konan::engine {
    ScriptSystem::ScriptSystem(bool& started)
        : started_ { started } {}

    void ScriptSystem::run() {
        if (!started_)
            return;

        for (auto& [_, script]: _world->filter<Script>())
            script.init();

        for (auto& [_, script]: _world->filter<Script>())
            script.run();
    }

    void ScriptSystem::destroy() {
        for (auto& [_, script]: _world->filter<Script>())
            script.destroy();
    }
}
