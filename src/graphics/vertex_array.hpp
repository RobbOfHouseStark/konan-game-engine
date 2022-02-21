#ifndef KGE_GRAPHICS_VERTEX_ARRAY_HPP
#define KGE_GRAPHICS_VERTEX_ARRAY_HPP

#include <cstddef>

#include "bindable.hpp"

namespace konan::graphics {
    struct VertexArray : public Bindable {
        // TODO: mustn't be here as well as renderer.
        virtual std::size_t vertices_size() const = 0;
        virtual std::size_t indices_size() const = 0;
    };
}

#endif  // KGE_GRAPHICS_VERTEX_ARRAY_HPP
