#ifndef KGE_EDITOR_GL_TEXTURE_HPP
#define KGE_EDITOR_GL_TEXTURE_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "texture.hpp"

namespace konan::graphics::opengl {
    struct OpenGlTexture : public Texture {
        OpenGlTexture(core::Tga const& tga, std::uint8_t slot);

        void bind(std::uint8_t slot) override;
        void unbind() override;

    private:
        std::uint32_t _id;
        std::uint8_t _current_slot;
    };
}

#endif //KGE_EDITOR_GL_TEXTURE_HPP
