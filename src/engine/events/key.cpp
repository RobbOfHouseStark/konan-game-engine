#include "key.hpp"

namespace konan::engine {
    Key::Key(int id, int scan_code, int action, int mods)
        : id { id }, scan_code { scan_code }, action { action }, mods { mods } {}
}
