#ifndef KGE_EDITOR_EDITOR_HPP
#define KGE_EDITOR_EDITOR_HPP

#include "exceptions.hpp"
#include "files.hpp"
#include "logging.hpp"

#include "gl_model.hpp"
#include "gl_shader.hpp"
#include "gl_vertex_array.hpp"
#include "gl_window.hpp"
#include "window.hpp"

#include "scene.hpp"

#include "systems/camera_movement_system.hpp"
#include "systems/event_system.hpp"
#include "systems/input_system.hpp"
#include "systems/render_system.hpp"

namespace konan::editor {
    struct Editor : public ecs::Scene {
        Editor();
    };
}

#endif  // KGE_EDITOR_EDITOR_HPP
