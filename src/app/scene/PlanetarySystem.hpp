/**
 * @file PlanetarySystem.hpp
 * @author sadekpet
 * @brief 
 * @date 2020-03-21
 * 
 */

#ifndef PGR_PLANETARY_SYSTEM_HPP
#define PGR_PLANETARY_SYSTEM_HPP

#include <core/scene/Node.hpp>

#include "Sun.hpp"
#include "Orbit.hpp"

namespace sadekpet {

class PlanetarySystem : public Node
{
public:
    void SetSun(Sun* sun);
    void AddOrbit(Orbit* orbit);
};

}

#endif // PGR_PLANETARY_SYSTEM_HPP