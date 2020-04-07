/**
 * @file Sun.hpp
 * @author sadekpet
 * @brief 
 * @date 2020-03-21
 * 
 */

#ifndef PGR_SUN_HPP
#define PGR_SUN_HPP

#include "SpaceBody.hpp"
#include "Sphere.hpp"

namespace sadekpet {

class Sun : public SpaceBody
{
private:
    SphereMaterial m_material;
public:
    Sun(float mass) : SpaceBody(mass) { m_material.GetUniforms().SetOwner(this); }
    Material& GetMaterial() override { return m_material; }
};

}

#endif // PGR_SUN_HPP