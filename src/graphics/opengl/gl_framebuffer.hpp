#ifndef KGE_GRAPHICS_GL_FRAMEBUFFER_HPP
#define KGE_GRAPHICS_GL_FRAMEBUFFER_HPP

#include <cassert>
#include <cstdint>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "framebuffer.hpp"

namespace konan::graphics::opengl {
    struct OpenGlFramebuffer : public Framebuffer {
        explicit OpenGlFramebuffer(std::uint32_t width, std::uint32_t height);

        void resize() override;
        void resize(std::uint32_t width, std::uint32_t height) override;

        std::uint32_t color_attachment() const override;
        std::uint32_t depth_attachment() const override;

        void bind() override;
        void unbind() override;

    private:
        std::uint32_t _width, _height;
        std::uint32_t _samples { 1 };
        bool _swap_chain_target {};

        std::uint32_t _color_attachment {}, _depth_attachment {};
    };
}

#endif  // KGE_GRAPHICS_GL_FRAMEBUFFER_HPP
