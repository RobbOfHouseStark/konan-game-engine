#ifndef KGE_GRAPHICS_GL_VERTEX_ARRAY_HPP
#define KGE_GRAPHICS_GL_VERTEX_ARRAY_HPP

#include <array>
#include <cstdint>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "files.hpp"
#include "gl_buffer.hpp"
#include "vertex_array.hpp"

namespace konan::graphics::opengl {
    struct OpenGlVertexLayout {
        explicit OpenGlVertexLayout(std::uint16_t stride);

        void add(std::uint8_t count);
        void apply() const;

    private:
        std::uint16_t _stride;
        std::vector<std::uint8_t> _layers;
    };

    struct OpenGlVertexArray : public VertexArray {
        OpenGlVertexArray(std::pair<std::vector<core::Vertex>, std::vector<core::VertexIndex>> const& data,
                          OpenGlVertexLayout const& vertex_layout);

        void bind() override;
        void unbind() override;

        std::size_t vertices_size() const override;
        std::size_t indices_size() const override;

    private:
        std::uint32_t _id;

        OpenGlBuffer _vbo;
        OpenGlBuffer _ibo;
    };
}

#endif  // KGE_GRAPHICS_GL_VERTEX_ARRAY_HPP
