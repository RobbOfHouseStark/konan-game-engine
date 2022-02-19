#include "button.hpp"

namespace konan::engine {
    Button::Button(int id, int action, int mods)
        : id { id }, action { action }, mods { mods } {}
}
