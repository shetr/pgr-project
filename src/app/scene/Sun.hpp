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
#include "ShaderContexts.hpp"

namespace sadekpet {

class Sun : public SpaceBody
{
private:
    Object3DShaderContext m_shaderContext;
public:
    Sun(float mass) : SpaceBody(mass), m_shaderContext("sphere", "perlinSun.png") {  }
    ShaderContext& GetShaderContext() override { return m_shaderContext; }
};

}

#endif // PGR_SUN_HPP