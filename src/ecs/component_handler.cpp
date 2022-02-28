#include "component_handler.hpp"
#include "world.hpp"

namespace konan::ecs {
    IComponentHandler::IComponentHandler() {
        World::register_component(this);
    }

    void IComponentHandler::set_one_frame(WorldId world_id) {
        one_frame.insert(world_id);
    }

    bool IComponentHandler::is_one_frame(WorldId world_id) {
        return one_frame.contains(world_id);
    }
}
