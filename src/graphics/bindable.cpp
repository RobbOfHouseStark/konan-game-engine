#include "bindable.hpp"

namespace konan::graphics {
    IBindable::IBindable(IBindable&& rhs) noexcept
        : id { rhs.id }, release { rhs.release } {
        rhs.id = 0;
        rhs.release = nullptr;
    }

    IBindable& IBindable::operator=(IBindable&& rhs) noexcept {
        if (id == rhs.id && release == rhs.release)
            return *this;

        id = rhs.id;
        release = rhs.release;
        rhs.id = 0;
        rhs.release = nullptr;

        return *this;
    }

    IBindable::~IBindable() {
        if (release != nullptr)
            release(id);
    }
}
