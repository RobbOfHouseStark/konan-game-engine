#ifndef KGE_ENGINE_KEY_HPP
#define KGE_ENGINE_KEY_HPP

namespace konan::engine {
    struct Key {
        Key(int id, int scan_code, int action, int mods);

    public:
        int id;
        int scan_code;
        int action;
        int mods;
    };
}

#endif  // KGE_ENGINE_KEY_HPP
