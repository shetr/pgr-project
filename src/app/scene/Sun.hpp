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

/**
 * @brief (spíše) Hvězda v planetárním systému. Mění svojí texturu s časem.
 */
class Sun : public SpaceBody
{
private:
    SunShaderContext m_shaderContext;
    float m_time;
    float m_changeSpeed;
public:
    Sun(float size, float density);
    ShaderContext& GetShaderContext() override { return m_shaderContext; }
    void Update(float deltaTime) override;
};

}

#endif // PGR_SUN_HPP