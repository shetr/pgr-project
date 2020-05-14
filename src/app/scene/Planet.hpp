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
    SphereShaderContext m_shaderContext;
public:
    Planet(float mass) : SpaceBody(mass) { m_shaderContext.GetUniforms().SetOwner(this); }
    ShaderContext& GetShaderContext() override { return m_shaderContext; }
};

}

#endif // PGR_PLANET_HPP