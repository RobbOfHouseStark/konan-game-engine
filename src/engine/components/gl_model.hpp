#ifndef KGE_ENGINE_MODEL_HPP
#define KGE_ENGINE_MODEL_HPP

#include "gl_shader.hpp"
#include "gl_texture.hpp"
#include "gl_vertex_array.hpp"

namespace konan::engine {
    struct OpenGlModel {
        void bind(std::uint8_t slot);
        void unbind();

    public:
        graphics::opengl::OpenGlShader shader;
        graphics::opengl::OpenGlTexture texture;
        graphics::opengl::OpenGlVertexArray vertex_array;
    };
}

#endif  // KGE_ENGINE_MODEL_HPP
