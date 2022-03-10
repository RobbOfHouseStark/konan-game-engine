#include "start_scene_system.hpp"

namespace konan::editor {
    StartSceneSystem::StartSceneSystem(ecs::Scene* scene, bool* scene_running)
        : scene_ { scene }, scene_running_ { scene_running } {}

    void StartSceneSystem::init() {
        world->one_frame<Start>();
        world->one_frame<End>();
    }

    void StartSceneSystem::run(double dt) {
        for (auto& [_, start]: world->filter<Start>()) {
            scene_->init();
            *scene_running_ = true;
        }

        for (auto& [_, end]: world->filter<End>()) {
            *scene_running_ = false;
            scene_->destroy();
        }
    }
}
