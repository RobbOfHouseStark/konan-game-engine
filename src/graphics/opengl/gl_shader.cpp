#include "gl_shader.hpp"

namespace {
    void validate_shader(std::uint32_t shader, GLenum type) {
        std::int32_t result;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
        if (result == GL_TRUE)
            return;

        std::int32_t length;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
        char* message { (char*) alloca(length * sizeof(char)) };
        glGetShaderInfoLog(shader, length, &length, message);
        glDeleteShader(shader);
        // TODO: move to config.
        throw konan::core::GlfwError("Failed to compile ", type == GL_VERTEX_SHADER ? "vertex" : "fragment",
                                     " shader. ", message);
    }

    std::uint32_t compile_shader(std::string_view data, GLenum type) {
        std::uint32_t id { glCreateShader(type) };
        const char* src { data.data() };
        glShaderSource(id, 1, &src, nullptr);
        glCompileShader(id);
        validate_shader(id, type);
        return id;
    }
}

namespace konan::graphics::opengl {
    OpenGlShader::OpenGlShader(std::vector<std::string> const& sources) {
        // TODO: move to config.
        std::vector<GLenum> shader_types { GL_VERTEX_SHADER, GL_FRAGMENT_SHADER };
        assert(sources.size() == shader_types.size());
        _id = glCreateProgram();

        attach_shaders({
            compile_shader(sources[0], shader_types[0]),
            compile_shader(sources[1], shader_types[1])
        });
    }

    void OpenGlShader::bind() {
        glUseProgram(_id);
    }

    void OpenGlShader::unbind() {
        glUseProgram(0);
    }

    void OpenGlShader::load_uniform(std::string_view name, glm::vec3 const& data) {
        auto location = glGetUniformLocation(_id, name.data());
        glUniform3f(location, data.x, data.y, data.z);
    }

    void OpenGlShader::load_uniform(std::string_view name, glm::mat4 const& data) {
        auto location = glGetUniformLocation(_id, name.data());
        glUniformMatrix4fv(location, 1, GL_FALSE, &data[0][0]);
    }

    void OpenGlShader::attach_shaders(std::vector<std::uint32_t> const& shaders) {
        for (auto shader: shaders)
            glAttachShader(_id, shader);
        glLinkProgram(_id);
        glValidateProgram(_id);
        for (auto shader: shaders) {
            glDetachShader(_id, shader);
            glDeleteShader(shader);
        }
    }
}
