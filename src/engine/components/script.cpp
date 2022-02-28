#include "script.hpp"

namespace konan::engine {
    void IScriptable::init() {}
    void IScriptable::run() {}
    void IScriptable::destroy() {}

    void IScriptable::owners(ecs::Entity* owner_entity, std::shared_ptr<ecs::World> owner_world) {
        entity = owner_entity;
        world = owner_world;
    }

    Script::Script(ecs::Entity entity)
        : entity_ { entity } {}

    Script& Script::add(std::shared_ptr<IScriptable> script) {
        scripts.push_back(script);
        return *this;
    }

    void Script::init() {
        for (auto script: scripts) {
            script->owners(&entity_.value(), entity_.value().world());
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
