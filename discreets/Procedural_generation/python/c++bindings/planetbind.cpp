#include "planets.hpp"
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>


namespace py = pybind11;

constexpr auto byref = py::return_value_policy::reference;


PYBIND11_MODULE(Elite_planets, m)
{
    py::class_<planet_generator:: Planet>(m,"Planet")
    .def("name",&planet_generator:: Planet::nm)
    .def("government",&planet_generator:: Planet::gov)
    .def("economy",&planet_generator:: Planet::eco)
    .def("technology",&planet_generator:: Planet::tech)
    .def("population",&planet_generator:: Planet::pop)
    .def("productivity",&planet_generator:: Planet::produc)
    .def("species",&planet_generator:: Planet::spec)
    .def("radius",&planet_generator:: Planet::radi)
    .def("has_ring",&planet_generator::Planet::has_ring)
    .def("color",&planet_generator::Planet::col)
    ;

    py::class_<planet_generator:: Planet_Sequence>(m,"Planets")
    .def(py::init<>())
    .def("get_planet",&planet_generator:: Planet_Sequence::current_planet,byref)
    .def("next_planet",&planet_generator::Planet_Sequence::next)
    ;
}