#include "button.hpp"

namespace konan::engine {
    Button::Button()
        : Button(0, 0, 0) {}

    Button::Button(int id, int action, int mods)
        : id { id }, action { action }, mods { mods } {}
}
