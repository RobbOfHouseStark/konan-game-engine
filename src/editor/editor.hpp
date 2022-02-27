#ifndef KGE_EDITOR_EDITOR_HPP
#define KGE_EDITOR_EDITOR_HPP

#include <yaml-cpp/yaml.h>

#include "exceptions.hpp"
#include "files.hpp"
#include "gl_framebuffer.hpp"
#include "gl_renderer.hpp"
#include "gl_shader.hpp"
#include "gl_texture.hpp"
#include "gl_vertex_array.hpp"
#include "gl_window.hpp"
#include "id.hpp"
#include "logging.hpp"
#include "scene.hpp"
#include "script.hpp"
#include "scripts/editor_cube.hpp"
#include "systems/camera_movement_system.hpp"
#include "systems/event_system.hpp"
#include "systems/input_system.hpp"
#include "systems/render_system.hpp"
#include "systems/script_system.hpp"
#include "window.hpp"

namespace konan::editor {
    struct Editor : public ecs::Scene {
        Editor();

    private:
        bool started_ { true };
    };
}

#endif  // KGE_EDITOR_EDITOR_HPP
