#ifndef KGE_CORE_FILES_HPP
#define KGE_CORE_FILES_HPP

#include <array>
#include <cstdint>
#include <cstring>
#include <fstream>
#include <sstream>
#include <string>
#include <tuple>
#include <unordered_map>
#include <utility>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtx/hash.hpp>

#include "exceptions.hpp"

namespace konan::core {
    using Vertex = std::array<float, 8>;
    using VertexIndex = std::uint32_t;

    struct Tga {
        bool alpha_channel() const {
            return bits_per_pixel == 32;
        }

    public:
        std::vector<std::uint8_t> pixels;
        std::uint32_t width, height, size, bits_per_pixel;
    };

    std::vector<std::string> load_glsl(std::string_view file_path);
    auto load_obj(std::string_view file_path)
                    -> std::pair<std::vector<Vertex>, std::vector<VertexIndex>>;

    Tga load_tga(std::string_view file_path);
}

#endif  // KGE_CORE_FILES_HPP
