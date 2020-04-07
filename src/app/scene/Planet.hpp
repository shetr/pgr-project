/**
 * @file Planet.hpp
 * @author sadekpet
 * @brief 
 * @date 2020-03-21
 * 
 */

#ifndef PGR_PLANET_HPP
#define PGR_PLANET_HPP

#include "SpaceBody.hpp"
#include "Sphere.hpp"

namespace sadekpet {

class Planet : public SpaceBody
{
private:
    SphereMaterial m_material;
public:
    Planet(float mass) : SpaceBody(mass) { m_material.GetUniforms().SetOwner(this); }
    Material& GetMaterial() override { return m_material; }
};

}

#endif // PGR_PLANET_HPP