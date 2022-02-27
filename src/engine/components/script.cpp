#include "script.hpp"

namespace konan::engine {
    void IScriptable::init() {}
    void IScriptable::run() {}
    void IScriptable::destroy() {}

    void IScriptable::owner(ecs::Entity* owner) {
        entity = owner;
    }

    Script::Script(ecs::Entity entity)
        : entity_ { entity } {}

    Script& Script::add(std::shared_ptr<IScriptable> script) {
        scripts.push_back(script);
        return *this;
    }

    void Script::init() {
        for (auto script: scripts) {
            script->owner(&entity_);
            script->init();
        }
    }

    void Script::run() {
        for (auto script: scripts)
            script->run();
    }

    void Script::destroy() {
        for (auto script: scripts)
            script->destroy();
    }
}
