#ifndef KGE_GRAPHICS_TEXTURE_HPP
#define KGE_GRAPHICS_TEXTURE_HPP

#include <cstdint>

#include "files.hpp"

namespace konan::graphics {
    struct Texture {
        virtual ~Texture() = default;

        virtual void bind(std::uint8_t slot) = 0;
        virtual void unbind() = 0;
    };
}

#endif  // KGE_GRAPHICS_TEXTURE_HPP
