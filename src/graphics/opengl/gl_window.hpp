#ifndef KGE_GRAPHICS_GL_WINDOW_HPP
#define KGE_GRAPHICS_GL_WINDOW_HPP

#include <cassert>
#include <functional>
#include <memory>
#include <vector>
#include <unordered_map>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "utility.hpp"
#include "exceptions.hpp"
#include "window.hpp"

namespace konan::graphics::opengl {
    using WindowHint = std::pair<int, int>;

    struct OpenGlWindow final : public Window {
        OpenGlWindow(std::uint16_t width, std::uint16_t height, std::string title, std::vector<WindowHint> const& hints);
        ~OpenGlWindow() final;

        void init_imgui() override;

        bool should_close() const override;
        void clear() override;
        void swap_buffers() override;
        void poll_events() override;

        void title(std::string) override;

        void swap_interval(bool on) override;
        void depth_test(bool on);
        void cull_face(bool on);

        void mouse_button_callback(MouseButtonCallback mbc) override;
        void key_callback(KeyCallback kc) override;
        std::pair<double, double> mouse_position() const override;
        void mouse_position(double x, double y) override;

    private:
        GLFWwindow* _window;
    };

    std::shared_ptr<Window> make_window(std::uint16_t width, std::uint16_t height, std::string const& title,
                                        std::uint8_t msaa, std::uint8_t major_version, std::uint8_t minor_version);
}

#endif  // KGE_GRAPHICS_GL_WINDOW_HPP
