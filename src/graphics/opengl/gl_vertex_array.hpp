#ifndef KGE_GRAPHICS_GL_VERTEX_ARRAY_HPP
#define KGE_GRAPHICS_GL_VERTEX_ARRAY_HPP

#include <array>
#include <execution>
#include <cstdint>
#include <numeric>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "files.hpp"
#include "gl_buffer.hpp"
#include "vertex_array.hpp"

namespace konan::graphics::opengl {
    struct OpenGlVertexLayout {
        explicit OpenGlVertexLayout(std::vector<std::uint8_t> layout);

        void apply() const;

    private:
        std::vector<std::uint8_t> _layout;
    };

    struct OpenGlVertexArray : public VertexArray {
        template <typename Vertex>
        OpenGlVertexArray(std::vector<Vertex> const& vbo_data, std::vector<std::uint32_t> const& ibo_data,
                          OpenGlVertexLayout const& vertex_layout)
            : _vbo { vbo_data, GL_ARRAY_BUFFER }, _ibo { ibo_data, GL_ELEMENT_ARRAY_BUFFER } {
            glGenVertexArrays(1, &id);
            release = [](std::uint32_t id) { glDeleteVertexArrays(1, &id); };

            glBindVertexArray(id);
            _vbo.bind();
            _ibo.bind();

            vertex_layout.apply();
        }

        void bind() override;
        void unbind() override;

        std::size_t vertices_size() const override;
        std::size_t indices_size() const override;

    private:
        OpenGlBuffer _vbo;
        OpenGlBuffer _ibo;
    };
}

#endif  // KGE_GRAPHICS_GL_VERTEX_ARRAY_HPP
