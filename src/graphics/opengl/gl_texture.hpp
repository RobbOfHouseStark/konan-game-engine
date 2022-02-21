#ifndef KGE_EDITOR_GL_TEXTURE_HPP
#define KGE_EDITOR_GL_TEXTURE_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "texture.hpp"

namespace konan::graphics::opengl {
    struct OpenGlTexture : public Texture {
        explicit OpenGlTexture(core::Tga const& tga);

        void bind() override;
        void unbind() override;
    };
}

#endif //KGE_EDITOR_GL_TEXTURE_HPP
