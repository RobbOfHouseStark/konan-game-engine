#include "gl_framebuffer.hpp"

namespace konan::graphics::opengl {
    OpenGlFramebuffer::OpenGlFramebuffer(std::uint32_t width, std::uint32_t height)
        : _width { width }, _height { height } {
        _release = [](std::uint32_t id) {
            glDeleteFramebuffers(1, &id);
        };

        resize();
    }

    void OpenGlFramebuffer::resize() {
        if (_id != 0) {
            glDeleteFramebuffers(1, &_id);
            glDeleteTextures(1, &_color_attachment);
            glDeleteTextures(1, &_depth_attachment);
        }

        glCreateFramebuffers(1, &_id);
        glBindFramebuffer(GL_FRAMEBUFFER, _id);
        glViewport(0, 0, _width, _height);;

        glGenTextures(1, &_color_attachment);
        glBindTexture(GL_TEXTURE_2D, _color_attachment);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                     _width, _height, 0,
                     GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _color_attachment, 0);

        glCreateTextures(GL_TEXTURE_2D, 1, &_depth_attachment);
        glBindTexture(GL_TEXTURE_2D, _depth_attachment);
        glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH24_STENCIL8, _width, _height);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, _depth_attachment, 0);

        assert(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void OpenGlFramebuffer::resize(std::uint32_t width, std::uint32_t height) {
        _width = width;
        _height = height;

        resize();
    }

    std::uint32_t OpenGlFramebuffer::color_attachment() const {
        return _color_attachment;
    }

    std::uint32_t OpenGlFramebuffer::depth_attachment() const {
        return _depth_attachment;
    }

    void OpenGlFramebuffer::bind() {
        glBindFramebuffer(GL_FRAMEBUFFER, _id);
        glViewport(0, 0, _width, _height);
    }

    void OpenGlFramebuffer::unbind() {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
}
