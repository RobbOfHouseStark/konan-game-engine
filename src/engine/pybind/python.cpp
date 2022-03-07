#include <pybind11/pybind11.h>

#include "entity_exposure.hpp"

namespace py = pybind11;

PYBIND11_MODULE(konan, handle) {
    handle.doc() = "Konan api for python.";
    handle.def("hello", &konan::engine::pybind::hello);
}
