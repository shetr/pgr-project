#include "PlanetarySystem.hpp"

#include <iostream>
#include <core/Console.hpp>

#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp> 

namespace sadekpet {

PlanetarySystem::PlanetarySystem(Sun* sun, MovableCamera* movCamera, const Shared<TimeGroup>& timeGroup, float sceneBorder) 
    : m_sun(sun), m_movCamera(movCamera), m_gravity(500), m_sceneBorder(sceneBorder)
{
    ConnectChild(sun);
    m_bodies.push_back(sun);
    SetTimeGroup(timeGroup);
    sun->SetTimeGroup(timeGroup);
    m_mouseButtonEventHandler = std::make_unique<MouseButtonEventHandler>(this, &PlanetarySystem::OnMouseButtonPressed, Input::Get());
}

void PlanetarySystem::AddOrbitToSun(Orbit* orbit)
{
    ConnectChild(orbit);
    AddOrbit(orbit);
}

void PlanetarySystem::AddOrbit(Orbit* orbit)
{
    m_orbits.push_back(orbit);
    orbit->SetTimeGroup(m_timeGroup);
    orbit->GetBody()->SetTimeGroup(m_timeGroup);
    m_bodies.push_back(orbit->GetBody());
}

void PlanetarySystem::Update(float deltaTime)
{
    Vector<uint> toErase;
    for(Pair<uint, Rocket*> pair : m_rockets) {
        Rocket* rocket = pair.second;
        glm::vec3 acceleration = glm::vec3(0);
        bool colided = false;
        for(SpaceBody* body : m_bodies) {
            glm::vec3 dir = body->GetWorldPos() - rocket->GetWorldPos();
            float dist = glm::length(dir);
            if(dist > 0.0001) {
                dist *= dist;
                dir = glm::normalize(dir);
                float accSize = m_gravity * body->GetMass() / dist;
                acceleration += accSize * dir;
                if(dist <= body->GetSize()) {
                    colided = true;
                }
            }
        }
        glm::vec3& speed = rocket->GetSpeed();
        glm::vec3 prevSpeed = speed;
        speed += acceleration * deltaTime;
        glm::quat q = glm::rotation(glm::vec3(0,0,-1), glm::normalize(speed));
        Transform& rocketTrans = rocket->GetTransform();
        rocketTrans.rotAngle = glm::angle(q);
        rocketTrans.rotAxis = glm::axis(q);
        rocketTrans.pos += speed * deltaTime;
        if(glm::length(rocketTrans.pos) > m_sceneBorder || colided) {
            toErase.push_back(rocket->GetID());
            delete rocket;
        }
    }
    for(uint id : toErase) {
        m_rockets.erase(id);
    }
}

void PlanetarySystem::OnMouseButtonPressed(const MouseButtonEvent& event)
{
    if(event.button == MouseButton::LEFT && event.pressed && m_movCamera->IsActive()) {
        SpawnRocket();
    }
}

void PlanetarySystem::SpawnRocket()
{
    Rocket* rocket = new Rocket(GetLayer());
    GetLayer()->Add(rocket);
    rocket->SetTimeGroup(m_timeGroup);
    ConnectChild(rocket);
    m_rockets.insert({rocket->GetID(), rocket});
    Transform& rocketTrans = rocket->GetTransform();
    Transform& movCamTrans = m_movCamera->GetTransform();
    Transform& camTrans = m_movCamera->GetCamera()->GetTransform();
    rocketTrans.pos = movCamTrans.pos;

    glm::quat q1 = glm::angleAxis(movCamTrans.rotAngle, movCamTrans.rotAxis);
    glm::quat q2 = glm::angleAxis(camTrans.rotAngle, camTrans.rotAxis);
    glm::quat q = q1 * q2;
    rocketTrans.rotAngle = glm::angle(q);
    rocketTrans.rotAxis = glm::axis(q);
    glm::vec3& speed = rocket->GetSpeed();
    speed = q * speed;
}

}