#include "PlanetarySystem.hpp"

namespace sadekpet {

PlanetarySystem::PlanetarySystem(Sun* sun) : m_sun(sun) 
{
    ConnectChild(sun);
}

void PlanetarySystem::AddOrbit(Orbit* orbit)
{
    m_orbits.push_back(orbit);
    m_sun->ConnectChild(orbit);
}

}