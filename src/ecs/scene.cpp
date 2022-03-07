#include "scene.hpp"

namespace konan::ecs {
    Scene::Scene(bool* running)
        : running { running }, world { std::make_shared<World>() }, systems { std::make_shared<Systems>(world) } {}

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
}
