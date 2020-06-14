#include "Ufo.hpp"

#include <core/manage/MaterialManager.hpp>
#include <core/scene/Layers.hpp>

#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp> 

namespace sadekpet {


Ufo::Ufo(const Vector<glm::vec3>& splinePoints, float speed, Layer* layer, const Shared<TimeGroup>& timeGroup)
    : m_spline(splinePoints), m_splinePos(0), m_speed(speed), m_rotSpeed(1)
{
    m_ufoParPar = new Node();
    m_ufoParPar->GetTransform().rotAxis = glm::vec3(0,1,0);
    m_transform.rotAxis = glm::vec3(1,0,0);
    ConnectChild(m_ufoParPar);
    m_ufoParent = new Node();
    m_ufoParent->GetTransform().rotAxis = glm::vec3(0,1,0);
    m_ufoParPar->ConnectChild(m_ufoParent);
    m_ufo = new Dummy("ufo", "ufo.jpg", MaterialManager::GetMaterial("ufo"));
    m_ufoParent->ConnectChild(m_ufo);
    m_ufo->GetTransform().scale /= 100;
    m_ufo->GetTransform().rotAxis = glm::vec3(1,0,0);
    m_ufo->GetTransform().rotAngle = M_PI/2;
    layer->Add(m_ufoParPar);
    layer->Add(m_ufoParent);
    layer->Add(m_ufo);
    m_transform.pos = m_spline.Value(m_splinePos);
    m_timeGroup = timeGroup;

    Camera* camera = new PerspectiveCamera(M_PI_2, 0.1f, 1000.0f);
    m_camera = new StaticCamera(camera);
    m_ufoParPar->ConnectChild(m_camera);
    m_camera->GetTransform().pos = glm::vec3(0, 0.5, 1);
    for(int l = 0; l < Layers::Count(); l++) {
        m_camera->AddLayer(Layers::Get(l));
    }
    layer->Add(camera);
    layer->Add(m_camera);
}

void Ufo::Update(float deltaTime)
{
    m_splinePos += m_speed * deltaTime;
    if(m_splinePos >= m_spline.GetLengthApprox()) {
        m_splinePos -= m_spline.GetLengthApprox();
    }
    m_transform.pos = m_spline.Value(m_splinePos);
    glm::vec3 d = glm::normalize(m_spline.Derivative(m_splinePos));
    m_transform.rotAngle = glm::asin(d.y);

    glm::vec3 d2 = glm::normalize(glm::vec3(d.x, 0, d.z));
    m_ufoParPar->GetTransform().rotAngle = d2.x >= 0 ? M_PI + glm::acos(d2.z) : M_PI - glm::acos(d2.z);
/*
    glm::quat q = glm::rotation(glm::vec3(0,0,-1), d);
    m_transform.rotAngle = glm::angle(q);
    m_transform.rotAxis = glm::axis(q);
*/
    m_ufoParent->GetTransform().rotAngle += m_rotSpeed * deltaTime;
    if(m_ufoParent->GetTransform().rotAngle > 2*M_PI) {
        m_ufoParent->GetTransform().rotAngle -= 2*M_PI;
    }
}

}