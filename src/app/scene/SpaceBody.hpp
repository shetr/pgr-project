/**
 * @file SpaceBody.hpp
 * @author sadekpet ()
 * @brief 
 * @date 2020-04-02
 * 
 */

#ifndef PGR_SPACE_BODY_HPP
#define PGR_SPACE_BODY_HPP

#include <core/scene/Node.hpp>

namespace sadekpet {

class SpaceBody : public VisibleNode
{
public:
    using Iterator = Set<SpaceBody*>::iterator;
private:
    static Set<SpaceBody*> s_bodies;
    float m_size;
    float m_density;
    uint8_t m_stencilId;
public:
    SpaceBody(float size, float density);
    ~SpaceBody();
    float GetSize() const { return m_size; }
    float GetDensity() const { return m_density; }
    float GetMass() const { return m_size * m_density; }

    static Iterator AllBegin() { return s_bodies.begin(); }
    static Iterator AllEnd() { return s_bodies.end(); }
    void SetStencilID(uint8_t id) { m_stencilId = id; }
    uint8_t GetStencilID() const override { return m_stencilId; }
};

}

#endif // PGR_SPACE_BODY_HPP