#ifndef KGE_ENGINE_RENDER_DATA_HPP
#define KGE_ENGINE_RENDER_DATA_HPP

#include <memory>

#include "graphics/framebuffer.hpp"

namespace konan::engine {
    struct RenderData {
        explicit RenderData(std::shared_ptr<graphics::Framebuffer> framebuffer);

    public:
        std::shared_ptr<graphics::Framebuffer> framebuffer;
    };
}

#endif  // KGE_ENGINE_RENDER_DATA_HPP
