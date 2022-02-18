#ifndef KGE_CORE_ASSERTION_HPP
#define KGE_CORE_ASSERTION_HPP

#include <utility>

namespace konan::core {
    template <typename Func>
    void if_debug(Func func) {
#ifndef NDEBUG
        func();
#endif
    }
}

#endif  // KGE_CORE_ASSERTION_HPP
