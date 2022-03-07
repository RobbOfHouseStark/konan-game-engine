#ifndef KGE_CORE_CLOCK_HPP
#define KGE_CORE_CLOCK_HPP

#include <chrono>
#include <cstdint>
#include <thread>

namespace konan::core {
    struct Clock {
        void tick(int fps = 0);
        double dt() const;
        double fps() const;

    private:
        std::chrono::steady_clock::time_point previous_time_ { std::chrono::high_resolution_clock::now() };
    };
}

#endif  // KGE_CORE_CLOCK_HPP
