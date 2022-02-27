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

    std::uint32_t compile_shader(std::string_view data, std::uint32_t type) {
        std::uint32_t id { glCreateShader(type) };
        const char* src { data.data() };
        glShaderSource(id, 1, &src, nullptr);
        glCompileShader(id);
        validate_shader(id, type);
        return id;
    }

    template <typename T>
    bool right_name_for_type(std::string_view type) {
        if constexpr (std::is_same_v<T, glm::vec2>) {
            return type.data() == std::string("vec2");
        } else if constexpr (std::is_same_v<T, glm::vec3>) {
            return type.data() == std::string("vec3");
        } else if constexpr (std::is_same_v<T, glm::vec4>) {
            return type.data() == std::string("vec4");
        } else if constexpr (std::is_same_v<T, glm::mat2>) {
            return type.data() == std::string("mat2");
        } else if constexpr (std::is_same_v<T, glm::mat3>) {
            return type.data() == std::string("mat3");
        } else if constexpr (std::is_same_v<T, glm::mat4>) {
            return type.data() == std::string("mat4");
        } else {
            assert(false);
        }
    }
}

namespace konan::graphics::opengl {
    OpenGlShader::OpenGlShader(std::vector<std::string> const& sources,
                               std::vector<std::uint32_t> const& shader_types,
                               std::unordered_map<std::string, std::string> uniforms)
                               : _uniforms { std::move(uniforms) } {
        assert(sources.size() == shader_types.size());

        id = glCreateProgram();
        release = glDeleteProgram;

        std::vector<std::uint32_t> shaders;
        for (int i {}; i < sources.size(); ++i)
            shaders.push_back(compile_shader(sources[i], shader_types[i]));

        attach_shaders(shaders);

        for (auto& [name, _]: _uniforms)
            _loaded_uniforms.emplace(name, false);
    }

    void OpenGlShader::load_uniform(std::string_view name, glm::vec2 const& data) {
        assert(_uniforms.find(name.data()) != _uniforms.end());
        assert(right_name_for_type<glm::vec2>(_uniforms[name.data()]));

        auto location { glGetUniformLocation(id, name.data()) };
        glUniform2f(location, data.x, data.y);

        _loaded_uniforms[name.data()] = true;
    }

    void OpenGlShader::load_uniform(std::string_view name, glm::vec3 const& data) {
        assert(_uniforms.find(name.data()) != _uniforms.end());
        assert(right_name_for_type<glm::vec3>(_uniforms[name.data()]));

        auto location { glGetUniformLocation(id, name.data()) };
        glUniform3f(location, data.x, data.y, data.z);

        _loaded_uniforms[name.data()] = true;
    }

    void OpenGlShader::load_uniform(std::string_view name, glm::mat4 const& data) {
        assert(_uniforms.find(name.data()) != _uniforms.end());
        assert(right_name_for_type<glm::mat4>(_uniforms[name.data()]));

        auto location { glGetUniformLocation(id, name.data()) };
        glUniformMatrix4fv(location, 1, GL_FALSE, &data[0][0]);

        _loaded_uniforms[name.data()] = true;
    }

    bool OpenGlShader::all_uniforms_loaded() const {
        return std::all_of(std::begin(_loaded_uniforms), std::end(_loaded_uniforms),
                    [this](auto& pair) {
                        auto it { _uniforms.find(pair.first) };
                        if (it->second == "sampler2D") return true;
                        return pair.second;
                    });
    }

    void OpenGlShader::bind() {
        glUseProgram(id);

        for (auto& [name, loaded]: _loaded_uniforms)
            loaded = false;
    }

    void OpenGlShader::unbind() {
        glUseProgram(0);
    }

    void OpenGlShader::attach_shaders(std::vector<std::uint32_t> const& shaders) {
        for (auto shader: shaders)
            glAttachShader(id, shader);
        glLinkProgram(id);
        glValidateProgram(id);
        for (auto shader: shaders) {
            glDetachShader(id, shader);
            glDeleteShader(shader);
        }
    }
}
