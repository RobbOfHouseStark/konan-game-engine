#ifndef KGE_ENGINE_SCRIPT_SYSTEM_HPP
#define KGE_ENGINE_SCRIPT_SYSTEM_HPP

#include "ecs/ecs.hpp"

#include "script.hpp"

namespace konan::engine {
    struct ScriptSystem : public ecs::IInitSystem,
                          public ecs::IRunSystem,
                          public ecs::IDestroySystem {
        void init() override;
        void run(double dt) override;
        void destroy() override;
    };
}

#endif  // KGE_ENGINE_SCRIPT_SYSTEM_HPP
