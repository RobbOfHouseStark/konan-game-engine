#ifndef KGE_ENGINE_ID_HPP
#define KGE_ENGINE_ID_HPP

#include <string>

namespace konan::engine {
    struct Id {
        Id(std::string tag, std::string name);

    public:
        std::string tag;
        std::string name;
    };
}

#endif  // KGE_ENGINE_ID_HPP
