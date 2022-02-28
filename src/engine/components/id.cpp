#include "id.hpp"

namespace konan::engine {
    Id::Id()
        : Id("Default", "Unnamed") {}

    Id::Id(std::string tag, std::string name)
        : tag { std::move(tag) }, name { std::move(name) } {}
}
