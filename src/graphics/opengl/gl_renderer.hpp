#ifndef KGE_GRAPHICS_GL_RENDERER_HPP
#define KGE_GRAPHICS_GL_RENDERER_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "renderer.hpp"

namespace konan::graphics::opengl {
    struct OpenGlRenderer : public Renderer {
        void draw(std::shared_ptr<Shader> shader,
                  std::shared_ptr<Texture> texture,
                  std::shared_ptr<VertexArray> vertex_array) override;
    };
}

#endif  // KGE_GRAPHICS_GL_RENDERER_HPP
