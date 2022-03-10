#ifndef KGE_ENGINE_SCRIPT_HPP
#define KGE_ENGINE_SCRIPT_HPP

#include <memory>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

#include "ecs/ecs.hpp"

namespace konan::engine {
    struct IScriptable {
        virtual ~IScriptable() = default;

        virtual void init();
        virtual void run(double dt);
        virtual void destroy();

        void owners(ecs::Entity* owner_entity, std::shared_ptr<ecs::World> owner_world);

    protected:
        ecs::Entity* entity;
        std::shared_ptr<ecs::World> world;
    };

    struct Script {
        explicit Script(ecs::Entity entity);

        template <typename T, typename... Ts>
        Script& add(Ts&& ... params) {
            return add(std::make_shared<T>(std::forward<Ts>(params)...));
        }

        Script& add(std::shared_ptr<IScriptable> script, std::string const& group = "GENERAL");

        void init(std::string const& group);
        void run(double dt, std::string const& group);
        void destroy(std::string const& group);

        void init();
        void run(double dt);
        void destroy();

    public:
        std::unordered_map<std::string, std::vector<std::shared_ptr<IScriptable>>> scripts;

    private:
        std::optional<ecs::Entity> entity_;
    };
}

#endif  // KGE_ENGINE_SCRIPT_HPP
