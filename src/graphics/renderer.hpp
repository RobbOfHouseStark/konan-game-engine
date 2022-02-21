#ifndef KGE_GRAPHICS_RENDERER_HPP
#define KGE_GRAPHICS_RENDERER_HPP

#include <memory>

#include <glm/glm.hpp>

#include "shader.hpp"
#include "texture.hpp"
#include "vertex_array.hpp"

namespace konan::graphics {
    struct Renderer {
        virtual void draw(std::shared_ptr<Shader> shader,
                          std::shared_ptr<Texture> texture,
                          std::shared_ptr<VertexArray> vertex_array) = 0;
    };
}

#endif  // KGE_GRAPHICS_RENDERER_HPP
