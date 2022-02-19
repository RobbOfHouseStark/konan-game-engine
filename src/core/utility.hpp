#ifndef KGE_CORE_UTILITY_HPP
#define KGE_CORE_UTILITY_HPP

#include <tuple>
#include <vector>

namespace konan::core {
    template <typename T>
    struct LambdaWrapper { using Type = T; };

    template <typename FrwrdIt, typename... FrwrdIts>
    auto zip(FrwrdIt begin, FrwrdIt end, FrwrdIts ... params) {
        std::vector<std::tuple<typename FrwrdIt::value_type, typename FrwrdIts::value_type...>> zipped;
        while (begin != end) {
            zipped.emplace_back(*begin, *params...);
            ++begin;
            (..., ++params);
        }
        return zipped;
    }
}

#endif  // KGE_CORE_UTILITY_HPP
