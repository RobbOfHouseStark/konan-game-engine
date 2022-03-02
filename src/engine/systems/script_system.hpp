#ifndef KGE_ENGINE_SCRIPT_SYSTEM_HPP
#define KGE_ENGINE_SCRIPT_SYSTEM_HPP

#include "ecs.hpp"
#include "script.hpp"

namespace konan::engine {
    struct ScriptSystem : public ecs::IInitSystem,
                          public ecs::IRunSystem,
                          public ecs::IDestroySystem {
        void init() override;
        void run() override;
        void destroy() override;
    };
}

#endif  // KGE_ENGINE_SCRIPT_SYSTEM_HPP
