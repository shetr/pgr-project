#include "PickPlanetController.hpp"

#include <core/scene/Layers.hpp>
#include <core/Window.hpp>
#include <core/Console.hpp>

#include <iostream>

namespace sadekpet {

PickPlanetController::PickPlanetController(const Vector<CameraController*>& ignoreCams, const Shared<CameraControll>& camControll)
    : m_ignoreCams(ignoreCams), m_selected(0), m_lastMouseDir(glm::vec3(0)), m_camControll(camControll)
{
    m_stencilUpdateEventHandler = std::make_unique<StencilUpdateEventHandler>(this, &PickPlanetController::OnStencilUpdate, Input::Get());
    m_mouseButtonEventHandler = std::make_unique<MouseButtonEventEventHandler>(this, &PickPlanetController::OnMouseButton, Input::Get());
}

void PickPlanetController::AddOrbit(Orbit* orbit)
{
    SpaceBody* body = orbit->GetBody();
    m_orbits.push_back(orbit);
    body->SetStencilID(m_orbits.size());
}

void PickPlanetController::OnStencilUpdate(const StencilUpdateEvent& event)
{
    for(CameraController* cam : m_ignoreCams) {
        if(cam->IsActive()) {
            return;
        }
    }
    MousePos pos = Input::GetMousePos();
    int stencilID = Input::GetStencilID(pos);
    if(m_selected == 0 && stencilID > 0 && stencilID <= m_orbits.size() && Input::IsMouseButtonPressed(MouseButton::LEFT)) {
        m_selected = stencilID;
        m_orbits[m_selected-1]->Show();
        WindowSize winSize = Window::GetSize();
        m_lastMouseDir = Layers::GetCurrent()->GetCurrentCamera()->GetMouseLookDir(winSize.width - pos.x, pos.y);
    }
}

void PickPlanetController::OnMouseButton(const MouseButtonEvent& event)
{
    if(event.button == MouseButton::LEFT && !event.pressed) {
        if(m_selected > 0) {
            m_orbits[m_selected-1]->Hide();
        }
        m_selected = 0;
    }
}

void PickPlanetController::Update(float deltaTime)
{
    if(m_selected > 0) {
        MousePos pos = Input::GetMousePos();
        WindowSize winSize = Window::GetSize();
        glm::vec3 mouseDir = m_camControll->GetActive()->GetCamera()->GetMouseLookDir(winSize.width - pos.x, pos.y);
        glm::vec3 camPos = m_camControll->GetActive()->GetTransform().pos;
        float t = -camPos.y / mouseDir.y;
        glm::vec3 mouseIntersection = glm::vec3(camPos.x + t*mouseDir.x, 0, camPos.z + t*mouseDir.z);
        Orbit* selected = m_orbits[m_selected-1];
        glm::vec3 planetPos = selected->GetBody()->GetWorldPos();
        glm::vec3 planetDir = glm::normalize(planetPos);
        glm::vec3 diff = mouseIntersection - planetPos;
        float moveSize = glm::length(diff);
        if(moveSize > 0.001f) {
            diff = glm::normalize(diff);
            glm::vec3 moveDir = glm::vec3(-planetDir.z,0,planetDir.x);
            moveSize *= glm::dot(moveDir, diff) * deltaTime;
            selected->Move(moveSize);
        }
    }
}

}