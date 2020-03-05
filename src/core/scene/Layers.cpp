#include "Layers.hpp"

namespace sadekpet{

Vector<Layer> Layers::s_layers;
UnordMap<String, size_t> Layers::s_namesToLayer;
Layer* Layers::s_current = nullptr;

}