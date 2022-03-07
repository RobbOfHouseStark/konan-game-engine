#include "clock.hpp"
#include "logging.hpp"

namespace konan::core {
    void Clock::tick(int fps) {
        double spent_time { dt() };
        previous_time_ = std::chrono::high_resolution_clock::now();

        if (fps != 0) {
            double time_to_sleep { (1 / static_cast<double>(fps)) - spent_time };
            if (time_to_sleep < 0)
                return;

            std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(time_to_sleep * 1000)));
        }
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
