#include "event_system.hpp"

namespace konan::engine {
    EventSystem::EventSystem(bool& running)
        : _running { running } {}

    void EventSystem::init() {
        window_ = _world->injection<graphics::Window>();
    }

    void EventSystem::run() {
        window_->poll_events();
        if (window_->should_close()) {
            _running = false;
        }
    }
}
