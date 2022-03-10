#include "clock.hpp"

namespace konan::core {
    void Clock::tick() {
        double spent_time { dt() };
        previous_time_ = std::chrono::high_resolution_clock::now();
    }

    double Clock::dt() const {
        return std::chrono::duration<double>(
            std::chrono::high_resolution_clock::now() - previous_time_
        ).count();
    }

    double Clock::fps() const {
        return 1 / dt();
    }
}
