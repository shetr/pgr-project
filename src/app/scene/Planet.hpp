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

class Planet : public SpaceBody
{
private:
    Object3DShaderContext m_shaderContext;
    Shared<Object3DShaderContextUpdater> m_shaderContextUpdater;
	float m_rotationSpeed;
    float m_texRot = 0;
public:
    Planet(float size, float density, const String& texture, float rotationSpeed = 1) 
        : SpaceBody(size, density), m_shaderContext("sphere", texture), m_rotationSpeed(rotationSpeed) {
        m_shaderContextUpdater = Shared<Object3DShaderContextUpdater>(new Object3DShaderContextUpdater(&m_shaderContext));
        AddShaderContextUpdater(m_shaderContextUpdater);
		GetTransform().rotAxis = glm::vec3(0, 1, 0);
    }
    ShaderContext& GetShaderContext() override { return m_shaderContext; }
	void Update(float deltaTime) override;
};

}

#endif // PGR_PLANET_HPP