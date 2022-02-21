#ifndef KGE_GRAPHICS_BINDABLE_BINDABLE_HPP
#define KGE_GRAPHICS_BINDABLE_BINDABLE_HPP

#include <cstdint>

namespace konan::graphics {
    using ReleaseCallback = void(*)(std::uint32_t);

    struct Bindable {
        Bindable() = default;
        Bindable(Bindable const&) = delete;
        Bindable& operator=(Bindable const&) = delete;
        Bindable(Bindable&& rhs) noexcept;
        Bindable& operator=(Bindable&& rhs) noexcept;
        virtual ~Bindable();

        virtual void bind() = 0;
        virtual void unbind() = 0;

    protected:
        std::uint32_t _id;
        ReleaseCallback _release;
    };
}

#endif  // KGE_GRAPHICS_BINDABLE_BINDABLE_HPP
