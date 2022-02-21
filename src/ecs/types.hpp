#ifndef KGE_ECS_TYPES_HPP
#define KGE_ECS_TYPES_HPP

#include <cstdint>
#include <functional>
#include <string>
#include <unordered_map>

namespace konan::ecs {
    using EntityId = std::uint32_t;
    using ComponentId = std::size_t;
    using InjectionId = std::size_t;

    struct World;
    struct Systems;
    template <typename Component>
    struct ComponentHandler;

    template <typename T>
    struct LambdaWrapper { using Type = T; };

    template <typename... Components>
    using FilterLambda = typename LambdaWrapper<std::function<void(EntityId, Components& ...)>>::Type;
}

#endif  // KGE_ECS_TYPES_HPP
