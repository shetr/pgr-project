#include "Orbit.hpp"

#include <app/generate/MeshGen.hpp>

namespace sadekpet {

Orbit::Orbit(SpaceBody* body, float radius, float speed, float start)
    : m_body(body), m_radius(radius), m_speed(speed), m_phi(start), 
    m_shaderContext(MeshGen::Cyrcle(radius, (uint)radius * 2 * M_PI * 10), 1, glm::vec3(0.2, 0.2, 0.2))
{
    m_shaderContextUpdater = Shared<Line3DShaderContextUpdater>(new Line3DShaderContextUpdater(&m_shaderContext));
    AddShaderContextUpdater(m_shaderContextUpdater);
    Hide();
    ConnectChild(body);
    m_body->GetTransform().pos = radius * glm::vec3(1,0,0);
}

void Orbit::Update(float deltaTime)
{
    glm::vec3& pos = m_body->GetTransform().pos;
    m_phi += deltaTime * m_speed;
    if(m_phi > 2*M_PI) m_phi -= 2*M_PI;
    pos.x = m_radius * glm::cos(m_phi);
    pos.z = m_radius * glm::sin(m_phi);
}

}