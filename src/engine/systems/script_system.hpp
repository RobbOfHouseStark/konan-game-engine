#ifndef KGE_ENGINE_SCRIPT_SYSTEM_HPP
#define KGE_ENGINE_SCRIPT_SYSTEM_HPP

#include "ecs.hpp"
#include "script.hpp"

namespace konan::engine {
    struct ScriptSystem : public ecs::IRunSystem,
                          public ecs::IDestroySystem {
    explicit ScriptSystem(bool& started);

    void run() override;
    void destroy() override;

    private:
        bool& started_;
    };
}

#endif  // KGE_ENGINE_SCRIPT_SYSTEM_HPP
