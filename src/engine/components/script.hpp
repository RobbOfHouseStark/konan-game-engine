#ifndef KGE_ENGINE_SCRIPT_HPP
#define KGE_ENGINE_SCRIPT_HPP

#include <memory>
#include <optional>
#include <vector>

#include "ecs.hpp"

namespace konan::engine {
    struct IScriptable {
        virtual ~IScriptable() = default;

        virtual void init();
        virtual void run();
        virtual void destroy();

        void owners(ecs::Entity* owner_entity, std::shared_ptr<ecs::World> owner_world);

    protected:
        ecs::Entity* entity;
        std::shared_ptr<ecs::World> world;
    };

    struct Script {
        Script() = default;
        explicit Script(ecs::Entity entity);

        template <typename T, typename... Ts>
        Script& add(Ts&& ... params) {
            scripts.emplace_back(std::make_shared<T>(std::forward<Ts>(params)...));
            return *this;
        }

        Script& add(std::shared_ptr<IScriptable> script);

        void init();
        void run();
        void destroy();

    public:
        std::vector<std::shared_ptr<IScriptable>> scripts;

    private:
        std::optional<ecs::Entity> entity_;
    };
}

#endif  // KGE_ENGINE_SCRIPT_HPP
