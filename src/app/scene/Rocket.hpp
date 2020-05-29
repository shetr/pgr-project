/**
 * @file Rocket.hpp
 * @author sadekpet (sadekpet@fel.cvut.cz)
 * @brief 
 * @date 2020-05-28
 * 
 */

#ifndef PGR_ROCKET_HPP
#define PGR_ROCKET_HPP

#include "Dummy.hpp"

namespace sadekpet {

class Rocket : public Node
{
private:
    Dummy* m_model;
    glm::vec3 m_speed = glm::vec3(0,0,-1);
    float m_mass = 1;
public:
    Rocket(Layer* layer) {
        Material mat;
        mat.shinines = 10;
        m_model = new Dummy("rocket", "red.png", mat);
        m_model->GetTransform().scale /= 10;
        ConnectChild(m_model);
        layer->Add(m_model);
        m_model->GetTransform().pos = glm::vec3(-2.65666, 1.17639, 3.72275) / 10.0f;
        m_model->GetTransform().rotAxis = glm::vec3(1,0,0);
        m_model->GetTransform().rotAngle = M_PI;
        m_speed *= 10;
    }
    float GetMass() const { return m_mass; }
    glm::vec3& GetSpeed() { return m_speed; }
};

}

#endif // PGR_ROCKET_HPP