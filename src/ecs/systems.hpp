#ifndef KGE_ECS_SYSTEMS_HPP
#define KGE_ECS_SYSTEMS_HPP

#include <memory>
#include <type_traits>
#include <vector>
#include <unordered_set>

#include "types.hpp"
#include "world.hpp"

namespace konan::ecs {
    struct ISystem {
        void world(std::shared_ptr<World> world);
        virtual ~ISystem() = default;

    protected:
        std::shared_ptr<World> _world;
    };

    struct IInitSystem : virtual ISystem {
        virtual void init() = 0;
    };

    struct IRunSystem : virtual ISystem {
        virtual void run() = 0;
    };

    struct IDestroySystem : virtual ISystem {
        virtual void destroy() = 0;
    };

    struct Systems : public IInitSystem,
                     public IRunSystem,
                     public IDestroySystem {
        explicit Systems(std::shared_ptr<World> owner) {
            world(owner);
        }

        template <typename System, typename... Ts>
        std::shared_ptr<System> add(Ts&& ... params) {
            auto system { std::make_shared<System>(std::forward<Ts>(params)...) };
            add(system);
            return system;
        }

        template <typename System>
        void add(std::shared_ptr<System> system) {
            static_assert(std::is_convertible_v<System, ISystem>, "System must be derived from ISystem.");

            system->world(_world);

            if constexpr (std::is_base_of_v<IInitSystem, System>) {
                _init_systems.push_back(system);
            }
            if constexpr (std::is_base_of_v<IRunSystem, System>) {
                _run_systems.push_back(system);
            }
            if constexpr (std::is_base_of_v<IDestroySystem, System>) {
                _destroy_systems.push_back(system);
            }
        }

        void init() override {
            for (auto system: _init_systems)
                system->init();
        }

        void run() override {
            for (auto system: _run_systems)
                system->run();
        }

        void destroy() override {
            for (auto system: _destroy_systems)
                system->destroy();
        }

    private:
        std::vector<std::shared_ptr<IInitSystem>> _init_systems;
        std::vector<std::shared_ptr<IRunSystem>> _run_systems;
        std::vector<std::shared_ptr<IDestroySystem>> _destroy_systems;
    };
}

#endif  // KGE_ECS_SYSTEMS_HPP
