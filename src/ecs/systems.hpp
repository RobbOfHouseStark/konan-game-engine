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
        void set_world(std::shared_ptr<World> owner);
        virtual ~ISystem() = default;

    protected:
        std::shared_ptr<World> world;
    };

    struct IInitSystem : virtual ISystem {
        virtual void init() = 0;
    };

    struct IRunSystem : virtual ISystem {
        virtual void run(double dt) = 0;
    };

    struct IDestroySystem : virtual ISystem {
        virtual void destroy() = 0;
    };

    struct Systems : public IInitSystem,
                     public IRunSystem,
                     public IDestroySystem {
        explicit Systems(std::shared_ptr<World> world) {
            set_world(world);
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

            system->set_world(world);

            if constexpr (std::is_base_of_v<IInitSystem, System>) {
                init_systems_.push_back(system);
            }
            if constexpr (std::is_base_of_v<IRunSystem, System>) {
                run_systems_.push_back(system);
            }
            if constexpr (std::is_base_of_v<IDestroySystem, System>) {
                destroy_systems_.push_back(system);
            }
        }

        void init() override {
            for (auto system: init_systems_)
                system->init();
        }

        void run(double dt) override {
            for (auto system: run_systems_)
                system->run(dt);
        }

        void destroy() override {
            for (auto system: destroy_systems_)
                system->destroy();
        }

    private:
        std::vector<std::shared_ptr<IInitSystem>> init_systems_;
        std::vector<std::shared_ptr<IRunSystem>> run_systems_;
        std::vector<std::shared_ptr<IDestroySystem>> destroy_systems_;
    };
}

#endif  // KGE_ECS_SYSTEMS_HPP
