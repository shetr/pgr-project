#include "Planet.hpp"

namespace sadekpet {


void Planet::Update(float deltaTime)
{
	/*
	float& angle = GetTransform().rotAngle;
	angle += deltaTime * m_rotationSpeed;
	if (angle > 2 * M_PI) angle -= 2 * M_PI; */
	m_texRot += deltaTime * m_rotationSpeed;
	if (m_texRot > 1) m_texRot -= 1;
	glm::mat3 texMat = glm::mat3(1);
	texMat[2][0] = m_texRot;
	m_shaderContextUpdater->GetUniforms().textureMat->value = texMat;
}

}