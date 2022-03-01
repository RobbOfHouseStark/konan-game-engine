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

    Script& Script::add(std::shared_ptr<IScriptable> script, std::string const& group) {
        script->owners(&entity_.value(), entity_.value().world());
        scripts[group].push_back(script);
        return *this;
    }

    void Script::init(std::string const& group) {
        for (auto script: scripts[group])
            script->init();
    }

    void Script::run(std::string const& group) {
        for (auto script: scripts[group])
            script->run();
    }

    void Script::destroy(std::string const& group) {
        for (auto script: scripts[group])
            script->destroy();
    }
}
