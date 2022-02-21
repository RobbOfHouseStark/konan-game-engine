#include "gl_vertex_array.hpp"

namespace konan::graphics::opengl {
    OpenGlVertexLayout::OpenGlVertexLayout(std::vector<std::uint8_t> layout)
        : _layout { std::move(layout) } {}

    void OpenGlVertexLayout::apply() const {
        auto stride { std::accumulate(_layout.begin(), _layout.end(), 0) * sizeof(float) };

        for (std::size_t i {}, offset {}; i < _layout.size(); ++i) {
            auto attribute_size { _layout[i] };
            glEnableVertexAttribArray(i);
            glVertexAttribPointer(i, attribute_size, GL_FLOAT, GL_FALSE, stride,
                                  reinterpret_cast<const void*>(offset));
            offset += attribute_size * sizeof(float);
        }
    }

    void OpenGlVertexArray::bind() {
        glBindVertexArray(_id);
        _vbo.bind();
        _ibo.bind();
    }

    void OpenGlVertexArray::unbind() {
        glBindVertexArray(0);
        _vbo.unbind();
        _ibo.unbind();
    }

    std::size_t OpenGlVertexArray::vertices_size() const {
        return _vbo.size();
    }

    std::size_t OpenGlVertexArray::indices_size() const {
        return _ibo.size();
    }
}
