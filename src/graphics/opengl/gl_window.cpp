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

    std::shared_ptr<konan::graphics::opengl::OpenGlWindow> init_window(std::uint16_t width, std::uint16_t height,
                                                                       std::string const& title, std::uint8_t msaa,
                                                                       std::uint8_t major_version,
                                                                       std::uint8_t minor_version) {
        // TODO: config.
        std::vector<konan::graphics::opengl::WindowHint> hints {
            std::make_pair(GLFW_SAMPLES, msaa),
            std::make_pair(GLFW_CONTEXT_VERSION_MAJOR, major_version),
            std::make_pair(GLFW_CONTEXT_VERSION_MINOR, minor_version),
            std::make_pair(GLFW_CLIENT_API, GLFW_OPENGL_API),
            std::make_pair(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE)
        };
        konan::core::if_debug([&hints]() { hints.emplace_back(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE); });
        return std::make_shared<konan::graphics::opengl::OpenGlWindow>(width, height, title, hints);
    }

    void init_glad() {
        if (!static_cast<bool>(gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)))
            throw konan::core::GlfwError("Failed to initialize GLAD.");
    }

    // void input_callback(bool insert, GLFWwindow* window, int id, int scan_code, int action, int mods, int func_id,
    //                     konan::graphics::MouseButtonCallback mbc = nullptr,
    //                     konan::graphics::KeyCallback kc = nullptr,
    //                     bool delete_world = false) {
    //     static std::unordered_map<GLFWwindow*,
    //         std::pair<konan::graphics::MouseButtonCallback, konan::graphics::KeyCallback>> s_windows_callbacks {};
    //
    //     if (delete_world) {
    //         s_windows_callbacks.clear();
    //         return;
    //     }
    //
    //     if (insert) {
    //         if (mbc != nullptr) {
    //             s_windows_callbacks[window].first = mbc;
    //         }
    //         if (kc != nullptr) {
    //             s_windows_callbacks[window].second = kc;
    //         }
    //     } else {
    //         if (func_id == 0) {
    //             s_windows_callbacks[window].first(id, action, id);
    //         } else {
    //             s_windows_callbacks[window].second(id, scan_code, action, id);
    //         }
    //     }
    // }
    //
    // void button_callback(GLFWwindow* window, int id, int action, int mods) {
    //     input_callback(false, window, id, 0, action, mods, 0);
    // }
    //
    // void key_callback(GLFWwindow* window, int id, int scan_code, int action, int mods) {
    //     input_callback(false, window, id, scan_code, action, mods, 1);
    // }

    konan::graphics::MouseButtonCallback s_mbc;
    konan::graphics::KeyCallback s_kc;
}

namespace konan::graphics::opengl {
    std::shared_ptr<Window> make_window(std::uint16_t width, std::uint16_t height, std::string const& title,
                                        std::uint8_t msaa, std::uint8_t major_version, std::uint8_t minor_version) {
        init_glfw();
        auto window { init_window(width, height, title, msaa, major_version, minor_version) };
        init_glad();
        window->swap_interval(true);
        window->depth_test(true);
        window->cull_face(true);
        return window;
    }

    OpenGlWindow::OpenGlWindow(std::uint16_t width, std::uint16_t height,
                               std::string title, std::vector<WindowHint> const& hints)
        : Window(width, height, std::move(title)), _window {} {
        for (auto[name, value]: hints)
            glfwWindowHint(name, value);

        _window = glfwCreateWindow(_width, _height, _title.c_str(), nullptr, nullptr);
        if (_window == nullptr)
            throw core::GlfwError("Failed to open GLFW window.");

        glfwMakeContextCurrent(_window);
    }

    OpenGlWindow::~OpenGlWindow() {
        glfwDestroyWindow(_window);
    }

    void OpenGlWindow::imgui_init() {
        ImGui::CreateContext();
        ImGui::StyleColorsDark();

        ImGuiIO& io = ImGui::GetIO();
        (void) io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

        ImGui_ImplGlfw_InitForOpenGL(_window, true);
        ImGui_ImplOpenGL3_Init("#version 330");
    }

    void OpenGlWindow::imgui_begin_frame() {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    void OpenGlWindow::imgui_end_frame() {
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
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
        if (on)
            glEnable(GL_DEPTH_TEST);
        else
            glDisable(GL_DEPTH_TEST);

        glDepthFunc(GL_LESS);
    }

    void OpenGlWindow::cull_face(bool on) {
        auto func { on ? glEnable : glDisable };
        func(GL_CULL_FACE);
    }

    void OpenGlWindow::title(std::string title) {
        Window::title(std::move(title));
        glfwSetWindowTitle(_window, _title.c_str());
    }

    void OpenGlWindow::mouse_button_callback(MouseButtonCallback mbc) {
        s_mbc = mbc;
        glfwSetMouseButtonCallback(_window,
                                   [](GLFWwindow* window, int id, int action, int mods) {
                                       s_mbc(id, action, mods);
                                   });
    }

    void OpenGlWindow::key_callback(KeyCallback kc) {
        s_kc = kc;
        glfwSetKeyCallback(_window,
                           [](GLFWwindow* window, int id, int scan_code, int action, int mods) {
                               s_kc(id, scan_code, action, mods);
                           });
    }

    void OpenGlWindow::mouse_position(double x, double y) {
        glfwSetCursorPos(_window, x, y);
    }

    std::pair<double, double> OpenGlWindow::mouse_position() const {
        double x, y;
        glfwGetCursorPos(_window, &x, &y);
        return { x, y };
    }
}
