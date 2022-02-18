#include "render_system.hpp"

namespace konan::engine {
    void RenderSystem::run() {
        _world->injection<graphics::Window>()->swap_buffers();
    }
}
