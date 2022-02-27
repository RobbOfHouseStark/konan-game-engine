#include "component_handler.hpp"
#include "world.hpp"

namespace konan::ecs {
    IComponentHandler::IComponentHandler() {
        World::register_component(this);
    }
}
