#include "event_system.hpp"

namespace konan::engine {
    EventSystem::EventSystem(bool* running)
        : _running { running } {}

    void EventSystem::run() {
        auto window { _world->injection<graphics::Window>() };
        window->poll_events();
        if (window->should_close()) {
            *_running = false;
        }
    }
}
