#include "window.hpp"

namespace konan::graphics {
    Window::Window(std::uint16_t width, std::uint16_t height, std::string title)
        : _width { width }, _height { height }, _title { std::move(title) } {
    }

    std::uint16_t Window::width() const {
        return _width;
    }

    std::uint16_t Window::height() const {
        return _height;
    }

    float Window::ration() const {
        float height { static_cast<float>(_height) },
            width { static_cast<float>(_width) };

        return height / width;
    }

    std::string const& Window::title() const {
        return _title;
    }

    void Window::title(std::string title) {
        _title = std::move(title);
    }
}
