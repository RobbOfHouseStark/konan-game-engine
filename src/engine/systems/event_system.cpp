#include "event_system.hpp"

namespace konan::engine {
    EventSystem::EventSystem(bool* running)
        : running_ { running } {}

    void EventSystem::init() {
        window_ = world->injection<graphics::Window>();
    }

    void EventSystem::run(double dt) {
        window_->poll_events();
        if (window_->should_close())
            *running_ = false;

        for (auto& [_, key]: world->filter<Key>()) {
            if (key.id == 'Q')
                *running_ = false;
        }

        window_->swap_buffers();
    }
}
