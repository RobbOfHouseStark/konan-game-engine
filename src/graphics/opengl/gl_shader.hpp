#ifndef KGE_GRAPHICS_GL_SHADER_HPP
#define KGE_GRAPHICS_GL_SHADER_HPP

#include <algorithm>
#include <cassert>
#include <string>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/hash.hpp>

#include "exceptions.hpp"
#include "utility.hpp"
#include "shader.hpp"

namespace konan::graphics::opengl {
    struct OpenGlShader : public Shader {
        explicit OpenGlShader(std::vector<std::string> const& sources);

        void bind() override;
        void unbind() override;

        void load_uniform(std::string_view name, glm::vec3 const& data) override;
        void load_uniform(std::string_view name, glm::mat4 const& data) override;

    private:
        void attach_shaders(std::vector<std::uint32_t> const& shaders);

    private:
        std::uint8_t _id;
    };
}

#endif  // KGE_GRAPHICS_GL_SHADER_HPP
