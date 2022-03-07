#include "script_system.hpp"

namespace konan::engine {
    void ScriptSystem::init() {
        for (auto& [_, script]: world->filter<Script>())
            script.init();
    }

    void ScriptSystem::run(double dt) {
        for (auto& [_, script]: world->filter<Script>())
            script.run();
    }

    void ScriptSystem::destroy() {
        for (auto& [_, script]: world->filter<Script>())
            script.destroy();
    }
}
