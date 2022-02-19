#ifndef KGE_GRAPHICS_VERTEX_ARRAY_HPP
#define KGE_GRAPHICS_VERTEX_ARRAY_HPP

#include <cstddef>

namespace konan::graphics {
    struct VertexArray {
        virtual ~VertexArray() = default;

        virtual void bind() = 0;
        virtual void unbind() = 0;

        virtual std::size_t vertices_size() const = 0;
        virtual std::size_t indices_size() const = 0;
    };
}

#endif  // KGE_GRAPHICS_VERTEX_ARRAY_HPP
