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
#include "ShaderContexts.hpp"

namespace sadekpet {

/**
 * @brief Objekt rotující kolem jiného objektu, myšleno v kombinaci s třídou Orbit.
 */
class OrbitingObject : public SpaceBody
{
private:
    Object3DShaderContext m_shaderContext;
    Shared<Object3DShaderContextUpdater> m_shaderContextUpdater;
	float m_rotationSpeed;
    float m_texRot = 0;
public:
    OrbitingObject(float size, float density, const String& texture, float rotationSpeed = 1);
    OrbitingObject(float size, float density, const String& texture, const String& optTexture, float rotationSpeed = 1);
    ShaderContext& GetShaderContext() override { return m_shaderContext; }
	void Update(float deltaTime) override;
};

using Planet = OrbitingObject;

}

#endif // PGR_PLANET_HPP