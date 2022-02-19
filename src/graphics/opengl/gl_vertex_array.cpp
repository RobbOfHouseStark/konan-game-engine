#include "gl_vertex_array.hpp"

namespace konan::graphics::opengl {
    OpenGlVertexLayout::OpenGlVertexLayout(std::uint16_t stride)
        : _stride { stride } {}

    void OpenGlVertexLayout::add(std::uint8_t count) {
        _layers.push_back(count);
    }

    void OpenGlVertexLayout::apply() const {
        std::uint64_t offset {};

        for (std::size_t i {}; i < _layers.size(); ++i) {
            glEnableVertexAttribArray(i);
            glVertexAttribPointer(i, _layers[i], GL_FLOAT, GL_FALSE, _stride,  reinterpret_cast<const void*>(offset));

            offset += _layers[i] * sizeof(float);
        }
    }

    OpenGlVertexArray::OpenGlVertexArray(
        std::pair<std::vector<core::Vertex>, std::vector<core::VertexIndex>> const& data,
        OpenGlVertexLayout const& vertex_layout)
        : _vbo { data.first, GL_ARRAY_BUFFER }, _ibo { data.second, GL_ELEMENT_ARRAY_BUFFER } {
        glGenVertexArrays(1, &_id);
        bind();
        vertex_layout.apply();
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
