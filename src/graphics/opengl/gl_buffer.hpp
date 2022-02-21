#ifndef KGE_GRAPHICS_GL_BUFFER_HPP
#define KGE_GRAPHICS_GL_BUFFER_HPP

#include <cstdint>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "bindable.hpp"

namespace konan::graphics::opengl {
    struct OpenGlBuffer : public Bindable {
        template<typename T>
        OpenGlBuffer(std::vector<T> const& data, GLenum type)
            : _type { type }, _size { data.size() } {
            glGenBuffers(1, &_id);
            _release = [](std::uint32_t id) { glDeleteBuffers(1, &id); };

            glBindBuffer(_type, _id);
            glBufferData(type, data.size() * sizeof(T), data.data(), GL_STATIC_DRAW);
        }

        void bind() override;
        void unbind() override;

        std::size_t size() const;

    private:
        std::uint32_t _id;
        GLenum _type;
        std::size_t _size;
    };
}

#endif  // KGE_GRAPHICS_GL_BUFFER_HPP
