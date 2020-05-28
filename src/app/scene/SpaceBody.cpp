#include "SpaceBody.hpp"

namespace sadekpet {

Set<SpaceBody*> SpaceBody::s_bodies;

SpaceBody::SpaceBody(float size, float density)
    : m_size(size), m_density(density), m_stencilId(0)
{
    m_transform.scale = glm::vec3(m_size);
    s_bodies.insert(this);
}

SpaceBody::~SpaceBody()
{
    s_bodies.erase(this);
}

}