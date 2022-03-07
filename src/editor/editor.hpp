#ifndef KGE_EDITOR_EDITOR_HPP
#define KGE_EDITOR_EDITOR_HPP

#include <nlohmann/json.hpp>

#include "core/exceptions.hpp"
#include "core/files.hpp"
#include "core/logging.hpp"
#include "ecs/ecs.hpp"
#include "engine/components/id.hpp"
#include "engine/components/render_data.hpp"
#include "engine/components/script.hpp"
#include "engine/systems/event_system.hpp"
#include "engine/systems/input_system.hpp"
#include "engine/systems/render_system.hpp"
#include "engine/systems/script_system.hpp"
#include "graphics/window.hpp"
#include "graphics/opengl/gl_framebuffer.hpp"
#include "graphics/opengl/gl_renderer.hpp"
#include "graphics/opengl/gl_shader.hpp"
#include "graphics/opengl/gl_texture.hpp"
#include "graphics/opengl/gl_vertex_array.hpp"
#include "graphics/opengl/gl_window.hpp"

#include "editor_camera.hpp"
#include "editor_cube.hpp"
#include "editor_ui.hpp"

namespace konan::editor {
   struct Editor : public ecs::Scene {
        Editor(bool* running);
   };
}

#endif  // KGE_EDITOR_EDITOR_HPP
