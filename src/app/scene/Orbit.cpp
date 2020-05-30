#include "Orbit.hpp"

#include <app/generate/MeshGen.hpp>

#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp> 

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
    if(m_move) {
        Move(deltaTime * m_speed);
    }
}


void Orbit::Move(float phi)
{
    Transform& bodyTrans = m_body->GetTransform();
    glm::vec3& pos = bodyTrans.pos;
    m_phi += phi;
    if(m_phi > 2*M_PI) m_phi -= 2*M_PI;
    glm::quat q = glm::angleAxis(m_phi, glm::vec3(0,-1,0));
    pos = q * (m_radius * glm::vec3(1,0,0));
}

}