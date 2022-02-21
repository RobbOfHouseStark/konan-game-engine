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
        auto end { std::end(iterable) };
        auto start { *begin };
        return std::accumulate(++begin, end, start,
                    [&separator](auto a, typename It::value_type b) {
                        return std::move(a) + separator + b;
                    });
    }
}

#endif  // KGE_CORE_ASSERTION_HPP
