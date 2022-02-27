#ifndef KGE_GRAPHICS_BINDABLE_BINDABLE_HPP
#define KGE_GRAPHICS_BINDABLE_BINDABLE_HPP

#include <cstdint>

namespace konan::graphics {
    using ReleaseCallback = void(*)(std::uint32_t);

    struct IBindable {
        IBindable() = default;
        IBindable(IBindable const&) = delete;
        IBindable& operator=(IBindable const&) = delete;
        IBindable(IBindable&& rhs) noexcept;
        IBindable& operator=(IBindable&& rhs) noexcept;
        virtual ~IBindable();

        virtual void bind() = 0;
        virtual void unbind() = 0;

    protected:
        std::uint32_t id;
        void(*release)(std::uint32_t);
    };
}

#endif  // KGE_GRAPHICS_BINDABLE_BINDABLE_HPP
