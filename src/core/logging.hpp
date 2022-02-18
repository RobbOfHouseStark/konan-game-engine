#ifndef KGE_CORE_LOGGING_HPP
#define KGE_CORE_LOGGING_HPP

#include <iostream>

namespace konan::core {
    template <typename T, typename... Ts>
    void print(std::ostream& os, T&& param, Ts&& ... params) {
        os << param << " ";

        if constexpr (sizeof...(Ts) != 0) {
            print(os, std::forward<Ts>(params)...);
        } else {
            os << '\n';
        }
    }

    template <typename... Ts>
    void log(Ts&& ... params) {
        print(std::cout, "[LOG]", std::forward<Ts>(params)...);
    }

    template <typename... Ts>
    void warn(Ts&& ... params) {
        print(std::cerr, "[WARNING]", std::forward<Ts>(params)...);
    }

    template <typename... Ts>
    void error(Ts&& ... params) {
        print(std::cerr, "[ERROR]", std::forward<Ts>(params)...);
    }
}

#endif  // KGE_CORE_LOGGING_HPP
