#include "editor.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace konan::editor {
    Editor::Editor() {
        // TODO: file system.

//        glfwInit();
//        GLFWwindow* window { glfwCreateWindow(800, 800, "Window.", nullptr, nullptr) };
//        glfwMakeContextCurrent(window);
//        gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);

        auto window { _world->inject<graphics::Window>(graphics::opengl::make_window(800, 800, "WindoW.")) };

//        auto shader_source { core::load_glsl("resources/shaders/default.glsl") };
//        graphics::opengl::OpenGlShader shader { shader_source };
//        shader.bind();
//
//        float positions[] {
//            -.5f, -.5f,
//            .5f, -.5f,
//            .5f, .5f,
//            -.5f, .5f
//        };
//
//        unsigned int indices[] {
//            0, 1, 2,
//            2, 3, 0
//        };
//
//        unsigned int vao, vbo, ibo;
//
//        glGenBuffers(1, &vbo);
//        glBindBuffer(GL_ARRAY_BUFFER, vbo);
//        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 8, positions, GL_STATIC_DRAW);
//
//        glGenVertexArrays(1, &vao);
//        glBindVertexArray(vao);
//
//        glGenBuffers(1, &ibo);
//        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
//        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)* 6, indices, GL_STATIC_DRAW);
//
//        glEnableVertexAttribArray(0);
//        glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, nullptr);
//
//        glBindVertexArray(0);
//        glBindBuffer(GL_ARRAY_BUFFER, 0);
//        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
//
//        while (!window->should_close()) {
////            glDrawArrays(GL_TRIANGLES, 0, 3);
//            shader.bind();
//            glBindVertexArray(vao);
//
//            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
//
//            glBindVertexArray(0);
//
//            window->swap_buffers();
//            window->poll_events();
//        }

//        _world->inject<graphics::Window>(graphics::opengl::make_window(800, 600, "WindoW."));
//
        auto shader_source { core::load_glsl("resources/shaders/default.glsl") };
        graphics::opengl::OpenGlShader shader { shader_source };

        auto bricks_model { core::load_obj("resources/models/bricks.obj") };
        auto bricks_tga { core::load_tga("resources/textures/bricks.tga") };

        graphics::opengl::OpenGlVertexLayout vertex_layout { 8 * sizeof(float) };
        vertex_layout.add(3);
        vertex_layout.add(2);
        vertex_layout.add(3);

        graphics::opengl::OpenGlVertexArray vertex_array { bricks_model, vertex_layout };
        graphics::opengl::OpenGlTexture bricks_texture { bricks_tga, 0 };

        auto wall1 { _world->new_entity() };
        _world->replace<engine::OpenGlModel>(wall1, engine::OpenGlModel { shader, bricks_texture, vertex_array });
        _world->replace<engine::Transform>(wall1, engine::Transform { { -6.f, 0.f, 0.f },
                                                                      { 0.f, 0.f, 0.f },
                                                                      { 1.f, 1.f, 1.f } });

        auto camera { _world->new_entity() };
        _world->replace<engine::Camera>(camera, engine::Camera { 45.f, _world->injection<graphics::Window>()->ration(),
                                                                 .1f, 500.f });
        _world->replace<engine::Transform>(camera, engine::Transform { { -4.5f, 0.f, -13.f },
                                                                       { 0.f, 0.f, 0.f },
                                                                       { 1.f, 1.f, 1.f }});

        _systems->add<engine::EventSystem>(&_running);
        _systems->add<engine::InputSystem>();
        _systems->add<CameraMovementSystem>(.06f, .004f);
        _systems->add<engine::RenderSystem>();
    }
}
