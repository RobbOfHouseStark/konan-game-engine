#include "core/clock.hpp"
#include "editor/editor.hpp"

int main() {
    using namespace konan;

    bool running { true };
    editor::Editor editor { &running };
    core::Clock clock {};

    editor.init();
    while (running) {
        clock.tick();
        editor.run(clock.dt());
    }
    editor.destroy();
}
