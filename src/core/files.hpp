#ifndef KGE_CORE_FILES_HPP
#define KGE_CORE_FILES_HPP

#include <algorithm>
#include <array>
#include <concepts>
#include <cstdint>
#include <cstring>
#include <fstream>
#include <optional>
#include <regex>
#include <span>
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
    struct Vertex {
        glm::vec3 position;
        glm::vec2 uv;
        glm::vec3 normal;
    };

    using VertexIndex = std::uint32_t;

    struct Wavefront {
        std::vector<core::Vertex> vertices;
        std::vector<VertexIndex> indices;
    };

    struct Tga {
        Tga(int width, int height, int bits_per_pixel)
            : width { width }, height { height },
              size { ((width * bits_per_pixel + 31) / 32) * 4 * height }, bits_per_pixel { bits_per_pixel } {
            pixels.resize(size);
        }

        inline bool alpha_channel() const {
            return bits_per_pixel == 32;
        }

    public:
        std::vector<std::uint8_t> pixels;
        int width, height, size, bits_per_pixel;
    };

    struct Glsl {
        std::vector<std::string> data;
        std::unordered_map<std::string, std::string> uniforms;
    };

    Wavefront load_wavefront(std::string_view file_path);
    Tga load_tga(std::string_view file_path);
    Glsl load_glsl(std::string_view line, std::vector<std::string> const& shader_types);
}

#endif  // KGE_CORE_FILES_HPP
