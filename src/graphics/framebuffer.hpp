#ifndef KGE_GRAPHICS_FRAMEBUFFER_HPP
#define KGE_GRAPHICS_FRAMEBUFFER_HPP

#include "bindable.hpp"

namespace konan::graphics {
    struct Framebuffer : public Bindable {
        virtual void resize() = 0;
        virtual void resize(std::uint32_t width, std::uint32_t height) = 0;

        virtual std::uint32_t color_attachment() const = 0;
        virtual std::uint32_t depth_attachment() const = 0;
    };
}

#endif  // KGE_GRAPHICS_FRAMEBUFFER_HPP
