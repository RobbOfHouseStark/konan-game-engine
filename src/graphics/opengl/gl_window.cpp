#include "gl_window.hpp"

namespace {
    void glfw_error_callback(int error_code, const char* description) {
        throw konan::core::GlfwError(std::to_string(error_code), description);
    }

    void init_glfw() {
        if (auto error_code { static_cast<bool>(glfwInit()) }; !error_code)
            throw konan::core::GlfwError("Failed to initialize GLFW, error code: ", std::to_string(error_code));

        glfwSetErrorCallback(glfw_error_callback);
    }

    std::shared_ptr<konan::graphics::Window> init_window(std::uint16_t width, std::uint16_t height,
                                                         std::string const& title) {
        // TODO: config.
        std::vector<konan::graphics::opengl::WindowHint> hints {
            std::make_pair(GLFW_SAMPLES, 8),
            std::make_pair(GLFW_CONTEXT_VERSION_MAJOR, 4),
            std::make_pair(GLFW_CONTEXT_VERSION_MINOR, 6),
            std::make_pair(GLFW_CLIENT_API, GLFW_OPENGL_API),
            std::make_pair(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE)
        };
        konan::core::if_debug([&hints]() { hints.emplace_back(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE); });

        auto window {std::make_shared<konan::graphics::opengl::OpenGlWindow>(width, height, title, hints)};
        window->swap_interval(true);
        window->depth_test(true);
        window->cull_face(true);
        return window;
    }

    void init_glad() {
        if (!static_cast<bool>(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)))
            throw konan::core::GlfwError("Failed to initialize GLAD.");
    }
}

namespace konan::graphics::opengl {
    std::shared_ptr<Window> make_window(std::uint16_t width, std::uint16_t height, std::string const& title) {
        init_glfw();
        std::shared_ptr<Window> window { init_window(width, height, title) };
        init_glad();
        return window;
    }

    OpenGlWindow::OpenGlWindow(std::uint16_t width, std::uint16_t height,
                               std::string title, std::vector<WindowHint> const& hints)
        : Window(width, height, std::move(title)), _window {} {
        for (auto [name, value]: hints)
            glfwWindowHint(name, value);

        _window = glfwCreateWindow(_width, _height, _title.c_str(), nullptr, nullptr);
        if (_window == nullptr)
            throw core::GlfwError("Failed to open GLFW window.");

        glfwMakeContextCurrent(_window);
    }

    bool OpenGlWindow::should_close() const {
        return glfwWindowShouldClose(_window);
    }

    void OpenGlWindow::clear() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void OpenGlWindow::swap_buffers() {
        glfwSwapBuffers(_window);
    }

    void OpenGlWindow::poll_events() {
        glfwPollEvents();
    }

    void OpenGlWindow::swap_interval(bool on) {
        glfwSwapInterval(on);
    }

    void OpenGlWindow::depth_test(bool on) {
        /*if (on)
            glEnable(GL_DEPTH_TEST);
        else
            glDisable(GL_DEPTH_TEST);

        glDepthFunc(GL_LESS);*/
    }

    void OpenGlWindow::cull_face(bool on) {
        /*auto func {on ? glEnable : glDisable};
        func(GL_CULL_FACE);*/
    }

    void OpenGlWindow::title(std::string title) {
        Window::title(std::move(title));
        glfwSetWindowTitle(_window, _title.c_str());
    }

    void OpenGlWindow::button_callback(GLFWmousebuttonfun callback) {
        glfwSetMouseButtonCallback(_window, callback);
    }

    void OpenGlWindow::key_callback(GLFWkeyfun callback) {
        glfwSetKeyCallback(_window, callback);
    }

    void OpenGlWindow::mouse_position_callback(GLFWcursorposfun callback) {
        glfwSetCursorPosCallback(_window, callback);
    }

    void OpenGlWindow::mouse_enter_callback(GLFWcursorenterfun callback) {
        glfwSetCursorEnterCallback(_window, callback);
    }
}
