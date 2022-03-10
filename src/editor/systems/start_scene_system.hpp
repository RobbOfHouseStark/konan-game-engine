#ifndef KGE_EDITOR_START_SCRIPTS_HPP
#define KGE_EDITOR_START_SCRIPTS_HPP

#include "ecs/ecs.hpp"
#include "engine/systems/script_system.hpp"

#include "events/start.hpp"
#include "events/end.hpp"

namespace konan::editor {
    struct StartSceneSystem : public ecs::IInitSystem,
                              public ecs::IRunSystem {
        StartSceneSystem(ecs::Scene* scene, bool* scene_running);

        void init() override;
        void run(double dt) override;

    private:
        ecs::Scene* scene_;
        bool* scene_running_;
    };
}

#endif  // KGE_EDITOR_START_SCRIPTS_HPP
