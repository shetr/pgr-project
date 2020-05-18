#include "PlanetarySystem.hpp"

namespace sadekpet {

PlanetarySystem::PlanetarySystem(Sun* sun, const Shared<TimeGroup>& timeGroup) : m_sun(sun) 
{
    ConnectChild(sun);
    SetTimeGroup(timeGroup);
    sun->SetTimeGroup(timeGroup);
}

void PlanetarySystem::AddOrbit(Orbit* orbit)
{
    m_orbits.push_back(orbit);
    ConnectChild(orbit);
    orbit->SetTimeGroup(m_timeGroup);
    orbit->GetBody()->SetTimeGroup(m_timeGroup);
}

}