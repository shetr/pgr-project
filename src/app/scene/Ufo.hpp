/**
 * @file Ufo.hpp
 * @author sadekpet (sadekpet@fel.cvut.cz)
 * @brief 
 * @date 2020-06-01
 */

#ifndef PGR_UFO_HPP
#define PGR_UFO_HPP

#include <core/scene/Node.hpp>
#include <core/math/Spline.hpp>

#include "Dummy.hpp"
#include "CameraController.hpp"

namespace sadekpet {

class Ufo : public Node
{
private:
    Dummy* m_ufo;
    Node* m_ufoParPar;
    Node* m_ufoParent;
    UniformBSpline m_spline;
    float m_splinePos;
    float m_speed;
    float m_rotSpeed;
    StaticCamera* m_camera;
public:
    Ufo(const Vector<glm::vec3>& splinePoints, float speed, Layer* layer, Layer* skyLayer, const Shared<TimeGroup>& timeGroup);
    void Update(float deltaTime) override;
    StaticCamera* GetCam() { return m_camera; }
};

}

#endif // PGR_UFO_HPP