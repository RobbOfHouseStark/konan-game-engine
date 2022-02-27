#ifndef KGE_ENGINE_SCRIPT_HPP
#define KGE_ENGINE_SCRIPT_HPP

#include <memory>
#include <vector>

#include "ecs.hpp"

namespace konan::engine {
    struct IScriptable {
        virtual ~IScriptable() = default;

        virtual void init();
        virtual void run();
        virtual void destroy();

        void owner(ecs::Entity* owner);

    protected:
        ecs::Entity* entity;
    };

    struct Script {
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
        ecs::Entity entity_;
    };
}

#endif  // KGE_ENGINE_SCRIPT_HPP
