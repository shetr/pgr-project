#include "PickPlanetController.hpp"

#include <core/scene/Layers.hpp>
#include <core/Window.hpp>

#include <iostream>

namespace sadekpet {

PickPlanetController::PickPlanetController()
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
    MousePos pos = Input::GetMousePos();
    WindowSize winSize = Window::GetSize();
    int stencilID = Input::GetStencilID(pos);
    glm::vec3 mouseDir = Layers::GetCurrent()->GetCurrentCamera()->GetMouseLookDir(winSize.width - pos.x, pos.y);
    if(stencilID != 0 && stencilID <= m_orbits.size()) {
        std::cout << pos.x << " " << pos.y << " " << stencilID << " " << mouseDir.x << " " << mouseDir.y << " " << mouseDir.z << std::endl;
        glm::vec3 planetPos = m_orbits[stencilID-1]->GetBody()->GetWorldPos();
        std::cout << planetPos.x << " " << planetPos.y << " " << planetPos.z << std::endl;
    }
}

}