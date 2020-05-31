#include "SpaceBody.hpp"

namespace sadekpet {

Set<SpaceBody*> SpaceBody::s_bodies;

SpaceBody::SpaceBody(float size, float density)
    : m_size(size), m_density(density), m_stencilId(0)
{
    s_bodies.insert(this);
    m_transform.scale = glm::vec3(size);
}

SpaceBody::~SpaceBody()
{
    s_bodies.erase(this);
}

}