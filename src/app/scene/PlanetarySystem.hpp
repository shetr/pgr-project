/**
 * @file PlanetarySystem.hpp
 * @author sadekpet
 * @brief 
 * @date 2020-03-21
 * 
 */

#ifndef PGR_PLANETARY_SYSTEM_HPP
#define PGR_PLANETARY_SYSTEM_HPP

#include <core/scene/Node.hpp>
#include <core/Input.hpp>

#include "Sun.hpp"
#include "Orbit.hpp"
#include "CameraController.hpp"
#include "Rocket.hpp"

namespace sadekpet {

class PlanetarySystem : public Node
{
    using MouseButtonEventHandler = ScopedEventHandler<MouseButtonEvent, PlanetarySystem>;
private:
    Sun* m_sun;
    Vector<Orbit*> m_orbits;
    Vector<SpaceBody*> m_bodies;
    MovableCamera* m_movCamera;
    Map<uint, Rocket*> m_rockets;
    float m_gravity;
    float m_sceneBorder;
    Unique<MouseButtonEventHandler> m_mouseButtonEventHandler;
public:
    PlanetarySystem(Sun* sun, MovableCamera* movCamera, const Shared<TimeGroup>& timeGroup, float sceneBorder);
    void AddOrbitToSun(Orbit* orbit);
    void AddOrbit(Orbit* orbit);
    size_t BodyCount() const { return m_bodies.size(); }
    SpaceBody* GetBody(size_t i) { return m_bodies[i]; }
    size_t OrbitCount() const { return m_orbits.size(); }
    Orbit* GetOrbit(size_t i) { return m_orbits[i]; }

    void Update(float deltaTime) override;

    void OnMouseButtonPressed(const MouseButtonEvent& event);
private:
    void SpawnRocket();
};

}

#endif // PGR_PLANETARY_SYSTEM_HPP