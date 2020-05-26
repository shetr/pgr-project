#include "SpaceBody.hpp"

namespace sadekpet {

Set<SpaceBody*> SpaceBody::s_bodies;

SpaceBody::SpaceBody(float mass)
    : m_mass(mass), m_stencilId(0)
{
    m_transform.scale = glm::vec3(mass);
    s_bodies.insert(this);
}

SpaceBody::~SpaceBody()
{
    s_bodies.erase(this);
}

}