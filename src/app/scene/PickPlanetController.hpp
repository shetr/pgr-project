/**
 * @file PickPlanetController.hpp
 * @author sadekpet
 * @brief 
 * @date 2020-05-26
 * 
 */

#ifndef PGR_PICK_PLANET_CONTROLLER_HPP
#define PGR_PICK_PLANET_CONTROLLER_HPP

#include <core/Input.hpp>

#include "CameraController.hpp"
#include "Orbit.hpp"

namespace sadekpet {

class PickPlanetController
{
    using StencilUpdateEventHandler = ScopedEventHandler<StencilUpdateEvent, PickPlanetController>;
    using MouseButtonEventEventHandler = ScopedEventHandler<MouseButtonEvent, PickPlanetController>;
private:
    Vector<Orbit*> m_orbits;
    Vector<CameraController*> m_ignoreCams;
    Shared<CameraControll> m_camControll;
    Unique<StencilUpdateEventHandler> m_stencilUpdateEventHandler;
    Unique<MouseButtonEventEventHandler> m_mouseButtonEventHandler;
    int m_selected;
    glm::vec3 m_lastMouseDir;
public:
    PickPlanetController(const Vector<CameraController*>& ignoreCams, const Shared<CameraControll>& camControll);
    void AddOrbit(Orbit* orbit);
    void OnStencilUpdate(const StencilUpdateEvent& event);
    void OnMouseButton(const MouseButtonEvent& event);
    void Update(float deltaTime);
};

}

#endif // PGR_PICK_PLANET_CONTROLLER_HPP