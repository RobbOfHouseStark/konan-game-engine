#include "editor.hpp"

namespace konan::editor {
    Editor::Editor(bool* running)
        : Scene(running) {
        // TODO: file system.
        // TODO: rename to m_name or to name_.
        // TODO: unbind after construction.
        // TODO: framebuffer component to camera, renderer taking arguments.
        // TODO: components without default constructors, remove all in world.

        nlohmann::json config;

        {
            std::ifstream config_file { "config.json" };
            config_file >> config;
        }

        std::vector<std::string> shader_types;
        std::vector<std::uint32_t> shader_ids;
        for (int i {}; i < config["opengl"]["shader-types"].size(); ++i) {
            shader_types.push_back(config["opengl"]["shader-types"][i]["name"].get<std::string>());
            shader_ids.push_back(config["opengl"]["shader-types"][i]["glad-id"].get<std::uint32_t>());
        }
        std::vector<std::uint8_t> vertex_layout_data;
        for (int i {}; i < config["opengl"]["vertex-layout"].size(); ++i)
            vertex_layout_data.push_back(config["opengl"]["vertex-layout"][i].get<std::uint8_t>());

        core::Glsl glsl_data { core::load_glsl("resources/shaders/default.glsl", shader_types) };
        auto brick_model { core::load_wavefront("resources/models/bricks.obj") };

        auto window { world->inject<graphics::Window>(graphics::opengl::make_window(
            config["window"]["size"]["x"].get<int>(),
            config["window"]["size"]["y"].get<int>(),
            config["window"]["title"].get<std::string>(),
            config["window"]["msaa"].get<std::uint8_t>(),
            config["opengl"]["version"]["major"].get<std::uint8_t>(),
            config["opengl"]["version"]["minor"].get<std::uint8_t>())) };

        auto shader { std::make_shared<graphics::opengl::OpenGlShader>(glsl_data.data, shader_ids, glsl_data.uniforms) };
        auto texture { std::make_shared<graphics::opengl::OpenGlTexture>(core::load_tga("resources/textures/bricks.tga")) };
        graphics::opengl::OpenGlVertexLayout vertex_layout { vertex_layout_data };
        auto bricks_vertex_array { std::make_shared<graphics::opengl::OpenGlVertexArray>(brick_model.vertices, brick_model
        .indices, vertex_layout) };

        auto camera { world->new_entity() };
        camera.replace<engine::Id>("Default", "Camera");
        camera.replace<engine::Camera>(45.f, world->injection<graphics::Window>()->ration(), .1f, 500.f);
        camera.replace<engine::Transform>(-2.f, 2.f, -10.f);
        camera.replace<engine::Script>(camera).add<EditorCamera>(.06f, .006f).add(std::make_shared<EditorUI>(), "UI");
        camera.replace<engine::RenderData>(std::make_shared<graphics::opengl::OpenGlFramebuffer>(window->width(),
                                                                                                 window->height()));

        auto wall1 { world->new_entity() };
        wall1.replace<engine::Id>("Default", "Wall");
        wall1.replace<engine::Model>(shader, texture, bricks_vertex_array);
        wall1.replace<engine::Transform>(-6.f, 0.f, 0.f);
        wall1.replace<engine::Script>(wall1).add<Cube>(1.f);

        auto renderer { std::make_shared<graphics::opengl::OpenGlRenderer>() };

        systems->add<engine::InputSystem>();
        systems->add<engine::EventSystem>(running);
        systems->add<engine::ScriptSystem>();
        systems->add<engine::RenderSystem>(renderer);
    }
}
