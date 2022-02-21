#include "gl_renderer.hpp"

namespace konan::graphics::opengl {
    void OpenGlRenderer::draw(std::shared_ptr<Shader> shader,
                              std::shared_ptr<Texture> texture,
                              std::shared_ptr<VertexArray> vertex_array) {
        assert(shader->all_uniforms_loaded());

        if (vertex_array->indices_size() != 0)
            glDrawElements(GL_TRIANGLES, vertex_array->indices_size(), GL_UNSIGNED_INT, nullptr);
        else
            glDrawArrays(GL_TRIANGLES, 0, vertex_array->vertices_size());
    }
}
