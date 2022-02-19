#include "gl_texture.hpp"

namespace konan::graphics::opengl {
    OpenGlTexture::OpenGlTexture(core::Tga const& tga, std::uint8_t slot)
        : _current_slot { slot } {
        glGenTextures(1, &_id);
        glActiveTexture(GL_TEXTURE0 + _current_slot);
        glBindTexture(GL_TEXTURE_2D, _id);
        glTexImage2D(GL_TEXTURE_2D, 0,
                     tga.alpha_channel() ? GL_RGBA : GL_RGB,
                     tga.width, tga.height, 0,
                     tga.alpha_channel() ? GL_BGRA : GL_BGR,
                     GL_UNSIGNED_BYTE, tga.pixels.data());

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glActiveTexture(GL_TEXTURE0 + _current_slot);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void OpenGlTexture::bind(std::uint8_t slot) {
        if (_current_slot != slot)
            unbind();

        _current_slot = slot;
        glActiveTexture(GL_TEXTURE0 + _current_slot);
        glBindTexture(GL_TEXTURE_2D, _id);
    }

    void OpenGlTexture::unbind() {
        glActiveTexture(GL_TEXTURE0 + _current_slot);
        glBindTexture(GL_TEXTURE_2D, 0);
        _current_slot = 0;
    }
}
