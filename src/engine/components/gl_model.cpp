#include "gl_model.hpp"

namespace konan::engine {
    void OpenGlModel::bind(std::uint8_t slot) {
        vertex_array.bind();
        shader.bind();
        texture.bind(slot);
    }

    void OpenGlModel::unbind() {
        texture.unbind();
        shader.unbind();
        vertex_array.unbind();
    }
}
