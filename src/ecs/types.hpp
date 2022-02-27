#ifndef KGE_ECS_TYPES_HPP
#define KGE_ECS_TYPES_HPP

#include <cstdint>
#include <functional>
#include <string>
#include <unordered_map>

namespace konan::ecs {
    using EntityId = std::uint32_t;
    using WorldId = std::uint32_t;

    struct Entity;
}

#endif  // KGE_ECS_TYPES_HPP
