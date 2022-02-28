#ifndef KGE_ENGINE_MOUSE_MOVE_HPP
#define KGE_ENGINE_MOUSE_MOVE_HPP

namespace konan::engine {
    struct MouseMove {
        MouseMove();
        MouseMove(double dx, double dy);

    public:
        double dx, dy;
    };
}

#endif  // KGE_ENGINE_MOUSE_MOVE_HPP
