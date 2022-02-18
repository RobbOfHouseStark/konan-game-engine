#ifndef KGE_EDITOR_EDITOR_HPP
#define KGE_EDITOR_EDITOR_HPP

#include "exceptions.hpp"
#include "files.hpp"
#include "logging.hpp"

#include "gl_window.hpp"
#include "window.hpp"

#include "scene.hpp"

#include "event_system.hpp"
#include "render_system.hpp"

namespace konan::editor {
    struct Editor : public ecs::Scene {
        Editor();
    };
}

#endif  // KGE_EDITOR_EDITOR_HPP
