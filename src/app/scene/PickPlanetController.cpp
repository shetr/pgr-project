#include "PickPlanetController.hpp"

#include <core/scene/Layers.hpp>
#include <core/Window.hpp>

#include <iostream>

namespace sadekpet {

PickPlanetController::PickPlanetController(const Vector<CameraController*>& ignoreCams)
    : m_ignoreCams(ignoreCams)
{
    m_stencilUpdateEventHandler = std::make_unique<StencilUpdateEventHandler>(this, &PickPlanetController::OnStencilUpdate, Input::Get());
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
    WindowSize winSize = Window::GetSize();
    int stencilID = Input::GetStencilID(pos);
    glm::vec3 mouseDir = Layers::GetCurrent()->GetCurrentCamera()->GetMouseLookDir(winSize.width - pos.x, pos.y);
    if(stencilID != 0 && stencilID <= m_orbits.size()) {
        glm::vec3 planetPos = m_orbits[stencilID-1]->GetBody()->GetWorldPos();
    }
    for(int i = 0; i < (int)m_orbits.size(); i++) {
        Orbit* orbit = m_orbits[i];
        if(orbit->IsVisible()) {
            if(i != stencilID - 1) {
                orbit->Hide();
            }
        } else {
            if(i == stencilID - 1) {
                orbit->Show();
            }
        }
    }
}

void PickPlanetController::Update(float deltaTime)
{

}

}