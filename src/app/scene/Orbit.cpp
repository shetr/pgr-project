#include "Orbit.hpp"

namespace sadekpet {

Orbit::Orbit(SpaceBody* body, float radius, float speed, float start)
    : m_body(body), m_radius(radius), m_speed(speed), m_phi(start)
{
    m_material.GetUniforms().SetOwner(this);
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