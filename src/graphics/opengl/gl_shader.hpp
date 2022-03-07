#ifndef KGE_GRAPHICS_GL_SHADER_HPP
#define KGE_GRAPHICS_GL_SHADER_HPP

#include <cassert>
#include <string>
#include <type_traits>
#include <unordered_map>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/hash.hpp>

#include "core/exceptions.hpp"

#include "shader.hpp"

namespace konan::graphics::opengl {
    struct OpenGlShader : public Shader {
        explicit OpenGlShader(std::vector<std::string> const& sources, std::vector<std::uint32_t> const& shader_types,
                              std::unordered_map<std::string, std::string> uniforms);

        void load_uniform(std::string_view name, glm::vec2 const& data) override;
        void load_uniform(std::string_view name, glm::vec3 const& data) override;
        void load_uniform(std::string_view name, glm::mat4 const& data) override;

        bool all_uniforms_loaded() const override;

        void bind() override;
        void unbind() override;

    private:
        void attach_shaders(std::vector<std::uint32_t> const& shaders);

    private:
        std::unordered_map<std::string, std::string> _uniforms;
        std::unordered_map<std::string, bool> _loaded_uniforms;
    };
}

#endif  // KGE_GRAPHICS_GL_SHADER_HPP
