#include "component_handler.hpp"
#include "world.hpp"

namespace konan::ecs {
    IComponentHandler::IComponentHandler() {
        World::register_component(this);
    }

    void IComponentHandler::set_one_frame() {
        one_frame = true;
    }

    bool IComponentHandler::is_one_frame() {
        return one_frame;
    }
}
