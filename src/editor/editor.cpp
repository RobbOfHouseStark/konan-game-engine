#include "editor.hpp"

namespace konan::editor {
    Editor::Editor() {
        // TODO: file system.
        // TODO: rename to m_name or to name_.
        // TODO: unbind after construction.
        // TODO: framebuffer component to camera, renderer taking arguments.

        YAML::Node config { YAML::LoadFile("config.yaml") };
        std::vector<std::string> shader_types;
        std::vector<std::uint32_t> shader_ids;
        for (int i {}; i < config["opengl"]["shader-types"].size(); ++i) {
            shader_types.push_back(config["opengl"]["shader-types"][i]["name"].as<std::string>());
            shader_ids.push_back(config["opengl"]["shader-types"][i]["glad-id"].as<std::uint32_t>());
        }
        std::vector<std::uint8_t> vertex_layout_data;
        for (int i {}; i < config["opengl"]["vertex-layout"].size(); ++i)
            vertex_layout_data.push_back(config["opengl"]["vertex-layout"][i].as<std::uint8_t>());

        core::GlslData glsl_data { core::load_glsl("resources/shaders/default.glsl", shader_types) };
        auto brick_model { core::load_obj("resources/models/bricks.obj") };

        auto window { _world->inject<graphics::Window>(graphics::opengl::make_window(
                config["window"]["size"]["x"].as<int>(),
                config["window"]["size"]["y"].as<int>(),
                config["window"]["title"].as<std::string>(),
                config["window"]["msaa"].as<std::uint8_t>(),
                    config["opengl"]["version"]["major"].as<std::uint8_t>(),
                    config["opengl"]["version"]["minor"].as<std::uint8_t>())) };

        auto shader { std::make_shared<graphics::opengl::OpenGlShader>(glsl_data.data, shader_ids, glsl_data.uniforms) };
        auto texture { std::make_shared<graphics::opengl::OpenGlTexture>(core::load_tga("resources/textures/bricks.tga")) };
        graphics::opengl::OpenGlVertexLayout vertex_layout { vertex_layout_data };
        auto bricks_vertex_array { std::make_shared<graphics::opengl::OpenGlVertexArray>(brick_model.first, brick_model.second, vertex_layout) };

        auto camera { _world->new_entity() };
        camera.replace<engine::Id>("Default", "Camera");
        camera.replace<engine::Camera>(45.f, _world->injection<graphics::Window>()->ration(), .1f, 500.f);
        camera.replace<engine::Transform>(-2.f, 2.f, -10.f);
        camera.replace<engine::Script>(camera).add<EditorCamera>(.06f, .006f).add(std::make_shared<EditorUI>(), "UI");
        camera.replace<engine::RenderData>(std::make_shared<graphics::opengl::OpenGlFramebuffer>(window->width(),
                                                                                                 window->height()));

        auto wall1 { _world->new_entity() };
        wall1.replace<engine::Id>("Default", "Wall");
        wall1.replace<engine::Model>(shader, texture, bricks_vertex_array);
        wall1.replace<engine::Transform>(-6.f, 0.f, 0.f);
        wall1.replace<engine::Script>(wall1).add<Cube>(1.f);

        auto renderer { std::make_shared<graphics::opengl::OpenGlRenderer>() };

        _systems->add<engine::EventSystem>(_running);
        _systems->add<engine::InputSystem>();
        _systems->add<engine::ScriptSystem>(started_);
        _systems->add<engine::RenderSystem>(renderer);
    }
}
