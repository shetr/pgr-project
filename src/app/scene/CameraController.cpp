#include "CameraController.hpp"

#include <glm/gtx/transform.hpp>
#include <core/Window.hpp>
#include <iostream>

namespace sadekpet {

CameraController::CameraController(Camera* camera, Layer* layer)
    : m_camera(camera), m_layer(layer), m_active(false)
{
    ConnectChild(m_camera); 
    Transform& camTrans = camera->GetTransform();
    camTrans.pos = glm::vec3(0,0,0);
    camTrans.rotAxis = glm::vec3(1,0,0);
    camTrans.rotAngle = 0;
    m_transform.rotAxis = glm::vec3(0,1,0);
    m_transform.rotAngle = 0;
}

void CameraController::Activate() 
{ 
    m_active = true;
    m_layer->SetCurrentCamera(m_camera);
    OnActivate();
}
void CameraController::Deactivate()
{ 
    m_active = false; 
    OnDeactivate();
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
    if(event.pressed && ('1' <= event.key && event.key < '1'+ControllerCount() || event.key == 'n')){
        size_t i = event.key - '1';
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
    m_mouseMoveHandler = std::make_unique<MouseMoveHandler>(this, &MovableCamera::OnMouseEvent, Input::Get());
    m_keyEventHandler = std::make_unique<KeyEventHandler>(this, &MovableCamera::OnKeyPressed, Input::Get());
}
void MovableCamera::Update(float deltaTime)
{
    if(IsActive() && Input::IsCursorInWindow()) {
        Transform& camTrans = GetCamera()->GetTransform();
        glm::vec3 upDir = m_transform.rotAxis;
        glm::vec3 lookDir = glm::rotate(m_transform.rotAngle, m_transform.rotAxis) * glm::vec4(0,0,-1, 0);
        glm::vec3 sideDir = glm::cross(lookDir, m_transform.rotAxis);
        float addForward = 0;
        float addSide = 0;
        float addUp = 0;
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
        if(Input::IsKeyPressed('q')) {
            addUp -= 1;
        }
        if(Input::IsKeyPressed('e')) {
            addUp += 1;
        }
        m_transform.pos += (addForward*lookDir + addSide*sideDir + addUp*upDir) * m_moveSpeed * deltaTime;
        LerpStep();
        
        m_actualDir = ((m_lerpSteps - m_lerpStep) * m_prevDir + m_lerpStep * m_nextDir) / m_lerpSteps;
        float sideRot = m_transform.rotAngle - m_actualDir.x * m_turnSpeed * deltaTime;
        float upRot = camTrans.rotAngle - m_actualDir.y * m_turnSpeed * deltaTime;
        if(sideRot > M_PI) { sideRot -= 2*M_PI; }
        else if(sideRot < -M_PI) { sideRot += 2*M_PI; }
        m_transform.rotAngle = sideRot;
        if(upRot < M_PI_2 && upRot > -M_PI_2) {
            camTrans.rotAngle = upRot;
        }
    }
}
void MovableCamera::OnActivate()
{
    Input::HideCursor();
}
void MovableCamera::OnDeactivate()
{
    Input::ShowCursor();
}

void MovableCamera::OnMouseEvent(const MouseMoveEvent& event)
{
    if(IsActive()) {
        WindowSize winSize = Window::GetSize();
        MousePos mousePos = event.pos;
        m_nextDir = glm::vec2(mousePos.x - winSize.width/2, mousePos.y - winSize.height/2);
        m_prevDir = m_actualDir;
        m_lerpStep = 1;
        if(m_nextDir.x != 0 || m_nextDir.y != 0) {
            Input::SetMousePosToCenter();
        }
    }
}

void MovableCamera::OnKeyPressed(const KeyEvent& event)
{
    if(event.pressed){
        if (event.key == 'p') {
            const glm::vec3& pos = m_transform.pos; 
            std::cout << "pos: " << pos.x << ", " << pos.y << ", " << pos.z << std::endl;
            float sideRot = m_transform.rotAngle;
            std::cout << "side rot: " << sideRot << std::endl;
            float upRot = GetCamera()->GetTransform().rotAngle;
            std::cout << "up rot: " << upRot << std::endl;
        }
    }
}

void MovableCamera::LerpStep()
{
    if(m_lerpStep < m_lerpSteps) {
        m_lerpStep++;
    }
}

}