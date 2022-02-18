#ifndef KGE_GRAPHICS_WINDOW_HPP
#define KGE_GRAPHICS_WINDOW_HPP

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

namespace konan::graphics {
    struct Window {
        Window(std::uint16_t width, std::uint16_t height, std::string title);
        virtual ~Window() = default;

        std::uint16_t width() const;
        std::uint16_t height() const;
        float ration() const;
        std::string const& title() const;
        virtual void title(std::string title);

        virtual bool should_close() const = 0;
        virtual void clear() = 0;
        virtual void swap_buffers() = 0;
        virtual void poll_events() = 0;
        virtual void swap_interval(bool on) = 0;

    protected:
        std::uint16_t _width;
        std::uint16_t _height;
        std::string _title;
    };
}

#endif  // KGE_GRAPHICS_WINDOW_HPP
