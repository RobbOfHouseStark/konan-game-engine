#ifndef KGE_ENGINE_MODEL_HPP
#define KGE_ENGINE_MODEL_HPP

#include <memory>

#include "graphics/shader.hpp"
#include "graphics/texture.hpp"
#include "graphics/vertex_array.hpp"

namespace konan::engine {
    struct Model {
        Model(std::shared_ptr<graphics::Shader> shader,
              std::shared_ptr<graphics::Texture> texture,
              std::shared_ptr<graphics::VertexArray> vertex_array);

        void bind();
        void unbind();

    public:
        std::shared_ptr<graphics::Shader> shader;
        std::shared_ptr<graphics::Texture> texture;
        std::shared_ptr<graphics::VertexArray> vertex_array;
    };
}

#endif  // KGE_ENGINE_MODEL_HPP
