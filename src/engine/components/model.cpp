#include "model.hpp"

namespace konan::engine {
    Model::Model(std::shared_ptr<graphics::Shader> shader,
                 std::shared_ptr<graphics::Texture> texture,
                 std::shared_ptr<graphics::VertexArray> vertex_array)
                 : shader { shader }, texture { texture }, vertex_array { vertex_array } {}

    void Model::bind() {
        vertex_array->bind();
        shader->bind();
        texture->bind();
    }

    void Model::unbind() {
        texture->unbind();
        shader->unbind();
        vertex_array->unbind();
    }
}
