#ifndef KGE_ENGINE_BUTTON_HPP
#define KGE_ENGINE_BUTTON_HPP

namespace konan::engine {
    struct Button {
        Button(int id, int action, int mods);

    public:
        int id;
        int action;
        int mods;
    };
}

#endif  // KGE_ENGINE_BUTTON_HPP
