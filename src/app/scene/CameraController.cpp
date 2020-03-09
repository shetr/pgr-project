#include "CameraController.hpp"

#include <glm/gtx/transform.hpp>

namespace sadekpet {

CameraController::CameraController(Camera* camera, Layer* layer)
    : m_camera(camera), m_layer(layer), m_active(false)
{
    ConnectChild(m_camera); 
}

void CameraController::Activate() 
{ 
    m_active = true;
    m_layer->SetCurrentCamera(m_camera);
}
void CameraController::Deactivate()
{ 
    m_active = false; 
}

void CameraControll::Set(size_t i)
{
    m_controllers[m_active]->Deactivate();
    m_controllers[m_active = i]->Activate();
}
void CameraControll::Next()
{
    Set((m_active + 1) % ControllerCount());
}

NumericCamControll::NumericCamControll() 
{
    m_keyEventHandler = std::make_unique<KeyEventHandler>(this, &NumericCamControll::OnKeyPressed, Input::Get());
}

void NumericCamControll::OnKeyPressed(const KeyEvent& event)
{
    if(event.pressed){
        size_t i = '1' - event.key;
        if(i >= 0 && i < ControllerCount()) {
            Set(i);
        } else if (event.key == 'n') {
            Next();
        }
    }
}


MovableCamera::MovableCamera(Camera* camera, Layer* layer)
    : CameraController(camera, layer)
{
    Transform& camTrans = camera->GetTransform();
    camTrans.pos = glm::vec3(0,0,0);
    camTrans.rotAxis = glm::vec3(1,0,0);
    camTrans.rotAngle = 0;
    m_transform.rotAxis = glm::vec3(0,1,0);
    m_transform.rotAngle = 0;
}
void MovableCamera::Update(float deltaTime)
{
    if(IsActive()) {
        Transform& camTrans = GetCamera()->GetTransform();
        glm::vec3 lookDir = glm::rotate(camTrans.rotAngle, m_transform.rotAxis) * glm::vec4(0,0,-1, 0);
        glm::vec3 sideDir = glm::cross(lookDir, m_transform.rotAxis);
        float addForward = 0;
        float addSide = 0;
        if(Input::IsKeyPressed('s')) {
            addForward -= 1;
        }
        if(Input::IsKeyPressed('w')) {
            addForward += 1;
        }
        if(Input::IsKeyPressed('a')) {
            addSide -= 1;
        }
        if(Input::IsKeyPressed('d')) {
            addSide += 1;
        }
        m_transform.pos += (addForward*lookDir + addSide*sideDir) * m_moveSpeed * deltaTime;
    }
}

}