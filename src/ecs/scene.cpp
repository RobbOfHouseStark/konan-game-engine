#include "scene.hpp"

namespace konan::ecs {
    Scene::Scene()
        : world { std::make_shared<World>() }, systems { std::make_shared<Systems>(world) } {}

    void Scene::init() {
        systems->init();
    }

    void Scene::run(double dt) {
        systems->run(dt);
        world->update();
    }

    void Scene::destroy() {
        systems->destroy();
    }

    std::shared_ptr<World> Scene::get_world() {
        return world;
    }

    std::shared_ptr<Systems> Scene::get_systems() {
        return systems;
    }
}
