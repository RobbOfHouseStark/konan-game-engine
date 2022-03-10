#ifndef KGE_EDITOR_RENDER_SYSTEM_HPP_HPP
#define KGE_EDITOR_RENDER_SYSTEM_HPP_HPP

#include "ecs/ecs.hpp"
#include "engine/components/camera.hpp"
#include "engine/components/model.hpp"
#include "engine/components/render_data.hpp"
#include "engine/components/transform.hpp"
#include "graphics/renderer.hpp"
#include "graphics/window.hpp"

namespace konan::editor {
    struct EditorRenderSystem : public ecs::IInitSystem, public ecs::IRunSystem {
        explicit EditorRenderSystem(std::shared_ptr<graphics::Renderer> renderer);

        void init() override;
        void run(double dt) override;

    private:
        std::shared_ptr<ecs::World> scene_world_;
        std::shared_ptr<graphics::Renderer> renderer_;
    };
}

#endif  // KGE_EDITOR_RENDER_SYSTEM_HPP_HPP
