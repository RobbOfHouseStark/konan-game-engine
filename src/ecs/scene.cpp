#include "scene.hpp"

namespace konan::ecs {
    void Scene::run() {
        _systems->init();
        while (_running) {
            _systems->run();
            _world->update();
        }
        _systems->destroy();
    }
}
