#include "PlanetarySystem.hpp"

#include <iostream>
#include <core/Console.hpp>

#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp> 

#include <stdlib.h>

#include "GlobalSceneState.hpp"

namespace sadekpet {

PlanetarySystem::PlanetarySystem(Sun* sun, MovableCamera* movCamera, const Shared<TimeGroup>& timeGroup, float sceneBorder) 
    : m_sun(sun), m_movCamera(movCamera), m_gravity(500), m_sceneBorder(sceneBorder)
{
    ConnectChild(sun);
    m_bodies.push_back(sun);
    SetTimeGroup(timeGroup);
    sun->SetTimeGroup(timeGroup);
    m_mouseButtonEventHandler = std::make_unique<MouseButtonEventHandler>(this, &PlanetarySystem::OnMouseButtonPressed, Input::Get());
    srand(165);
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
        for(SpaceBody* body : m_bodies) {
            glm::vec3 dir = body->GetWorldPos() - rocket->GetWorldPos();
            float dist = glm::length(dir);
            if(dist > 0.0001) {
                dist *= dist;
                dir = glm::normalize(dir);
                float accSize = m_gravity * body->GetMass() / dist;
                acceleration += accSize * dir;
            }
        }
        glm::vec3& speed = rocket->GetSpeed();
        glm::vec3 prevSpeed = speed;
        speed += acceleration * deltaTime;
        glm::vec3 speedNorm = glm::normalize(speed);
        glm::quat q = glm::rotation(glm::vec3(0,0,-1), glm::normalize(speed));
        Transform& rocketTrans = rocket->GetTransform();
        rocketTrans.rotAngle = glm::angle(q);
        rocketTrans.rotAxis = glm::axis(q);
        rocketTrans.pos += speed * deltaTime;
        float speedSize = glm::length(speed);

        glm::vec3 frontPos = rocketTrans.pos + speedNorm;
        bool colided = false;
        for(SpaceBody* body : m_bodies) {
            glm::vec3 dir = body->GetWorldPos() - frontPos;
            float dist = glm::length(dir);
            if(dist <= body->GetSize()) {
                colided = true;
                break;
            }
        }
        rocket->smokeTimeout += deltaTime * rocket->smokeSpeed * speedSize;
        if(rocket->smokeTimeout > 1) {
            rocket->smokeTimeout = 0;
            SpawnSmoke(rocketTrans.pos - 0.25f * speedNorm, -speedNorm);
        }
        if(glm::length(rocketTrans.pos) > m_sceneBorder || colided) {
            SpawnExplosion(rocketTrans.pos + 0.5f * speedNorm, -speedNorm);
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

void PlanetarySystem::SpawnExplosion(glm::vec3 pos, glm::vec3 dir)
{
    int count = 1;
    float minSize = 1.5f;
    float radius = 0;
    for(int i = 1; i <= 3; i++) {
        for(int j = 0; j < count; j++) {
            glm::vec3 off = radius * RandDir();
            float size = minSize + RandFloat() * (minSize / 2.0f);
            float rot = 2*M_PI* RandFloat();
            float t = radius * 0.1 * RandFloat();
            GlobalSceneState::explosionParticleSystem->Spawn(ParticleVertex(pos + off, size, rot, t));
        }
        count *= 4;
        minSize /= 2;
        radius += 0.25;
    }
}

void PlanetarySystem::SpawnSmoke(glm::vec3 pos, glm::vec3 dir)
{
    int count = 3 + rand() % 1;
    for(int i = 0; i < count; i++) {
        glm::vec3 off = 0.05f * RandDir() + RandFloat() * dir;
        float size = 0.2 + RandFloat() * 0.1f;
        float rot = 2*M_PI* RandFloat();
        GlobalSceneState::smokeParticleSystem->Spawn(ParticleVertex(pos + off, size, rot, 0));
    }
}


glm::vec3 PlanetarySystem::RandDir()
{
    return glm::vec3(RandDirFloat(), RandDirFloat(), RandDirFloat());
}
float PlanetarySystem::RandFloat()
{
    return (float)(rand() % 10001) / 10000.0f;
}
float PlanetarySystem::RandDirFloat()
{
    return 2.0f*RandFloat() - 1.0f;
}

}