#include "script.hpp"

namespace konan::engine {
    void IScriptable::init() {}
    void IScriptable::run(double dt) {}
    void IScriptable::destroy() {}

    void IScriptable::owners(ecs::Entity* owner_entity, std::shared_ptr<ecs::World> owner_world) {
        entity = owner_entity;
        world = owner_world;
    }

    Script::Script(ecs::Entity entity)
        : entity_ { entity } {}

    Script& Script::add(std::shared_ptr<IScriptable> script, std::string const& group) {
        script->owners(&entity_.value(), entity_.value().world());
        scripts[group].push_back(script);
        return *this;
    }

    void Script::init(std::string const& group) {
        for (auto script: scripts[group])
            script->init();
    }

    void Script::run(double dt, std::string const& group) {
        for (auto script: scripts[group])
            script->run(dt);
    }

    void Script::destroy(std::string const& group) {
        for (auto script: scripts[group])
            script->destroy();
    }

    void Script::init() {
        for (auto& [_, group]: scripts) {
            for (auto script: group)
                script->init();
        }
    }

    void Script::run(double dt) {
        for (auto& [_, group]: scripts) {
            for (auto script: group)
                script->run(dt);
        }
    }

    void Script::destroy() {
        for (auto& [_, group]: scripts) {
            for (auto script: group)
                script->destroy();
        }
    }
}
