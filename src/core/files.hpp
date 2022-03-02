#ifndef KGE_CORE_FILES_HPP
#define KGE_CORE_FILES_HPP

#include <array>
#include <cstdint>
#include <cstring>
#include <fstream>
#include <regex>
#include <sstream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtx/hash.hpp>

#include "exceptions.hpp"
#include "utility.hpp"

namespace konan::core {
    struct GlslData {
        std::vector<std::string> data;
        std::unordered_map<std::string, std::string> uniforms;
    };

    struct Tga {
        inline bool alpha_channel() const {
            return bits_per_pixel == 32;
        }

    public:
        std::vector<std::uint8_t> pixels;
        std::uint32_t width, height, size, bits_per_pixel;
    };

    // TODO: rewrite with config and regexs.
    auto load_obj(std::string_view file_path)
                    -> std::pair<std::vector<std::array<float, 8>>, std::vector<std::uint32_t>>;
    Tga load_tga(std::string_view file_path);
    GlslData load_glsl(std::string_view file_path, std::vector<std::string> const& shader_types);
}

#endif  // KGE_CORE_FILES_HPP
