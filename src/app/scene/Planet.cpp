#include "Planet.hpp"

namespace sadekpet {


void Planet::Update(float deltaTime)
{
	float& angle = GetTransform().rotAngle;
	angle += deltaTime * m_rotationSpeed;
	if (angle > 2 * M_PI) angle -= 2 * M_PI;
}

}