#include "mouse_move.hpp"

namespace konan::engine {
    MouseMove::MouseMove()
        : MouseMove(0, 0) {}

    MouseMove::MouseMove(double dx, double dy)
        : dx { dx }, dy { dy } {}
}
