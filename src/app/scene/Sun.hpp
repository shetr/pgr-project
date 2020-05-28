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
    Basic3DShaderContext m_shaderContext;
public:
    Sun(float size, float density) : SpaceBody(size, density), m_shaderContext("sphere", "perlinSun.png") {  }
    ShaderContext& GetShaderContext() override { return m_shaderContext; }
};

}

#endif // PGR_SUN_HPP