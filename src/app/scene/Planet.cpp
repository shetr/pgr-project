#include "Planet.hpp"

namespace sadekpet {

OrbitingObject::OrbitingObject(float size, float density, const String& texture, float rotationSpeed) 
	: SpaceBody(size, density), m_shaderContext("sphere", texture), m_rotationSpeed(rotationSpeed) {
	m_shaderContextUpdater = Shared<Object3DShaderContextUpdater>(new Object3DShaderContextUpdater(&m_shaderContext));
	AddShaderContextUpdater(m_shaderContextUpdater);
	GetTransform().rotAxis = glm::vec3(0, 1, 0);
}

OrbitingObject::OrbitingObject(float size, float density, const String& texture, const String& optTexture, float rotationSpeed) 
	: SpaceBody(size, density), m_shaderContext("sphere", texture, optTexture), m_rotationSpeed(rotationSpeed) {
	m_shaderContextUpdater = Shared<Object3DShaderContextUpdater>(new Object3DShaderContextUpdater(&m_shaderContext));
	AddShaderContextUpdater(m_shaderContextUpdater);
	GetTransform().rotAxis = glm::vec3(0, 1, 0);
	m_shaderContextUpdater->GetUniforms().useOptTexture->value = true;
}

void OrbitingObject::Update(float deltaTime)
{
	m_texRot += deltaTime * m_rotationSpeed;
	if (m_texRot > 1) m_texRot -= 1;
	glm::mat3 texMat = glm::mat3(1);
	texMat[2][0] = m_texRot;
	m_shaderContextUpdater->GetUniforms().textureMat->value = texMat;
}

}