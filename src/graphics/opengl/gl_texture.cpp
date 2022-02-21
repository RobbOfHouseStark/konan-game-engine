#include "gl_texture.hpp"

namespace konan::graphics::opengl {
    OpenGlTexture::OpenGlTexture(core::Tga const& tga) {
        glGenTextures(1, &_id);
        _release = [](std::uint32_t id) {
            glDeleteTextures(1, &id);
        };

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, _id);
        glTexImage2D(GL_TEXTURE_2D, 0,
                     tga.alpha_channel() ? GL_RGBA : GL_RGB,
                     tga.width, tga.height, 0,
                     tga.alpha_channel() ? GL_BGRA : GL_BGR,
                     GL_UNSIGNED_BYTE, tga.pixels.data());

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void OpenGlTexture::bind() {
        // TODO: change slot.
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, _id);
    }

    void OpenGlTexture::unbind() {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}
