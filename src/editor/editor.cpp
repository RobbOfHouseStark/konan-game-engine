#include "editor.hpp"

namespace konan::editor {
    Editor::Editor() {
        // TODO: file system.
        // TODO: rename to m_name or to name_.
        // TODO: unbind after destruction.
        // TODO: versions from yaml to glfw init.
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

        _world->inject<graphics::Window>(graphics::opengl::make_window(
                config["window"]["size"]["x"].as<int>(),
                config["window"]["size"]["y"].as<int>(),
                config["window"]["title"].as<std::string>(),
                config["window"]["msaa"].as<std::uint8_t>(),
                    config["opengl"]["version"]["major"].as<std::uint8_t>(),
                    config["opengl"]["version"]["minor"].as<std::uint8_t>()));

        auto shader { std::make_shared<graphics::opengl::OpenGlShader>(glsl_data.data, shader_ids, glsl_data.uniforms) };
        auto texture { std::make_shared<graphics::opengl::OpenGlTexture>(core::load_tga("resources/textures/bricks.tga")) };
        graphics::opengl::OpenGlVertexLayout vertex_layout { vertex_layout_data };
        auto bricks_vertex_array { std::make_shared<graphics::opengl::OpenGlVertexArray>(brick_model.first, brick_model.second, vertex_layout) };

        auto camera { _world->new_entity() };
        _world->replace<engine::Id>(camera, "Default", "Camera");
        _world->replace<engine::Camera>(camera, 45.f, _world->injection<graphics::Window>()->ration(), .1f, 500.f);
        _world->replace<engine::Transform>(camera, -2.f, 2.f, -10.f);

        auto wall1 { _world->new_entity() };
        _world->replace<engine::Id>(wall1, "Default", "Wall");
        _world->replace<engine::Model>(wall1, shader, texture, bricks_vertex_array);
        _world->replace<engine::Transform>(wall1, -6.f, 0.f, 0.f);

        auto renderer { std::make_shared<graphics::opengl::OpenGlRenderer>() };

        _systems->add<engine::EventSystem>(&_running);
        _systems->add<engine::InputSystem>();
        _systems->add<CameraMovementSystem>(.06f, .004f);
        _systems->add<engine::RenderSystem>(renderer, std::make_shared<graphics::opengl::OpenGlFramebuffer>(800, 600));
    }
}
