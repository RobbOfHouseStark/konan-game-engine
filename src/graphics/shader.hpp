#ifndef KGE_GRAPHICS_SHADER_HPP
#define KGE_GRAPHICS_SHADER_HPP

#include <glm/glm.hpp>
#include <glm/gtx/hash.hpp>

#include "bindable.hpp"
#include "texture.hpp"

namespace konan::graphics {
    struct Shader : public IBindable {
        virtual void load_uniform(std::string_view name, glm::vec2 const& data) = 0;
        virtual void load_uniform(std::string_view name, glm::vec3 const& data) = 0;
        virtual void load_uniform(std::string_view name, glm::mat4 const& data) = 0;

        virtual bool all_uniforms_loaded() const = 0;
    };
}

#endif  // KGE_GRAPHICS_SHADER_HPP
