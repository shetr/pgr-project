/**
 * @file Orbit.hpp
 * @author sadekpet
 * @brief 
 * @date 2020-03-21
 * 
 */

#ifndef PGR_ORBIT_HPP
#define PGR_ORBIT_HPP

#include <core/scene/Node.hpp>
#include "SpaceBody.hpp"
#include "Sphere.hpp"

namespace sadekpet {

class Orbit : public VisibleNode
{
private:
    SphereMaterial m_material;
    SpaceBody* m_body;
    float m_radius;
    float m_speed;
    float m_phi;
public:
    Orbit(SpaceBody* body, float radius = 1, float speed = 1, float start = 0);

    void Update(float deltaTime) override;
    Material& GetMaterial() override { return m_material; }
};

}

#endif // PGR_ORBIT_HPP