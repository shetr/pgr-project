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
    SphereShaderContext m_shaderContext;
public:
    Sun(float mass) : SpaceBody(mass) {  }
    ShaderContext& GetShaderContext() override { return m_shaderContext; }
};

}

#endif // PGR_SUN_HPP