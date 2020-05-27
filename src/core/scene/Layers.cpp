#include "Layers.hpp"

namespace sadekpet{

Vector<Layer*> Layers::s_layers;
Layer* Layers::s_current = nullptr;

}