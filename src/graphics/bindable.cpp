#include "bindable.hpp"

namespace konan::graphics {
    Bindable::Bindable(Bindable&& rhs) noexcept
        : _id { rhs._id }, _release { rhs._release } {
        rhs._id = 0;
        rhs._release = nullptr;
    }

    Bindable& Bindable::operator=(Bindable&& rhs) noexcept {
        if (_id == rhs._id && _release == rhs._release)
            return *this;

        _id = rhs._id;
        _release = rhs._release;
        rhs._id = 0;
        rhs._release = nullptr;

        return *this;
    }

    Bindable::~Bindable() {
        if (_release != nullptr)
            _release(_id);
    }
}
