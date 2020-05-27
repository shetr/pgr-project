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
private:
    Vector<Orbit*> m_orbits;
    Vector<CameraController*> m_ignoreCams;
    Unique<StencilUpdateEventHandler> m_stencilUpdateEventHandler;
public:
    PickPlanetController(const Vector<CameraController*>& ignoreCams);
    void AddOrbit(Orbit* orbit);
    void OnStencilUpdate(const StencilUpdateEvent& event);
};

}

#endif // PGR_PICK_PLANET_CONTROLLER_HPP