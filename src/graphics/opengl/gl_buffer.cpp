#include "gl_buffer.hpp"

namespace konan::graphics::opengl {
    void OpenGlBuffer::bind() {
        glBindBuffer(_type, _id);
    }

    void OpenGlBuffer::unbind() {
        glBindBuffer(_type, 0);
    }

    std::size_t OpenGlBuffer::size() const {
        return _size;
    }
}
