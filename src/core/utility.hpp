#ifndef KGE_CORE_ASSERTION_HPP
#define KGE_CORE_ASSERTION_HPP

#include <numeric>
#include <string>

namespace konan::core {
    template <typename Func>
    void if_debug(Func func) {
#ifndef NDEBUG
        func();
#endif
    }

    template <typename It, typename T>
    auto join(It const& iterable, T const& separator) {
        auto begin { std::begin(iterable) };
        auto initial_value { *begin };
        auto end { std::end(iterable) };
        return std::accumulate(++begin, end, initial_value,
                    [&separator](auto a, auto b) {
                        return std::move(a) + separator + std::move(b);
                    });
    }
}

#endif  // KGE_CORE_ASSERTION_HPP
