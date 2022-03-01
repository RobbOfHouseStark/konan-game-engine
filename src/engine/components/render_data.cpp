#include "render_data.hpp"

namespace konan::engine {
    RenderData::RenderData(std::shared_ptr<graphics::Framebuffer> framebuffer)
        : framebuffer { framebuffer } {}
}
