#ifndef KGE_GRAPHICS_SHADER_HPP
#define KGE_GRAPHICS_SHADER_HPP

#include <glm/glm.hpp>
#include <glm/gtx/hash.hpp>

namespace konan::graphics {
    struct Shader {
        virtual ~Shader() = default;

        virtual void bind() = 0;
        virtual void unbind() = 0;

        virtual void load_uniform(std::string_view name, glm::vec3 const& data) = 0;
        virtual void load_uniform(std::string_view name, glm::mat4 const& data) = 0;
    };
}

#endif  // KGE_GRAPHICS_SHADER_HPP
