#include "App.hpp"

#include <iostream>

#include <core/Engine.hpp>
#include <core/Window.hpp>
#include <core/manage/ShaderManager.hpp>
#include <core/manage/TextureManager.hpp>
#include <core/manage/PrimitivesManager.hpp>
#include <core/scene/Layers.hpp>
#include <core/scene/Camera.hpp>
#include <app/scene/CameraController.hpp>

#include <app/scene/PlanetarySystem.hpp>
#include <app/scene/Planet.hpp>
#include <app/generate/MeshGen.hpp>
#include <app/scene/ShaderContexts.hpp>
#include <app/testing/Rectangle.hpp>
#include <app/testing/Sphere.hpp>
#include <app/testing/Testing.hpp>

namespace sadekpet {

App::App()
{}
App::~App()
{}

void App::Init()
{
    m_mouseEnterHandler = std::make_unique<MouseEnterHandler>(this, &App::OnMouseEnter, Input::Get());
    m_keyEventHandler = std::make_unique<KeyEventHandler>(this, &App::OnKeyPressed, Input::Get());
    m_specialKeyEventHandler = std::make_unique<SpecialKeyEventHandler>(this, &App::OnSpecialKeyPressed, Input::Get());
    ShaderManager::AddRenderProgram(TypeIndex(typeid(RectangleShaderContext)), "rectangle");
    ShaderManager::AddRenderProgram(TypeIndex(typeid(Object3DShaderContext)), "object3D");
    ShaderManager::AddRenderProgram(TypeIndex(typeid(Basic3DShaderContext)), "basic3D");
    TextureManager::AddTexture2D("sun.png");
    TextureManager::AddTexture2D("perlinSun.png");
    TextureManager::AddTexture2D("planet1.png");
    TextureManager::AddTexture2D("planet2.png");
    TextureManager::AddTexture2D("planet3.png");
    TextureManager::AddTexture2D("planet5.png");
    TextureManager::AddTexture2D("planet6.png");
    TextureManager::AddTexture2D("earth.jpg");
    PrimitivesManager::AddPrimitives("sphere", MeshGen::BasicSphere(30));
    Layer& layer = Layers::Get(Layers::Add("3D"));

    //g_GenTextures();

    m_planetarySystemTimeGroup = Shared<TimeGroup>(new TimeGroup());

    Sun* sun = new Sun(5);
    m_planetarySystem = new PlanetarySystem(sun, m_planetarySystemTimeGroup);
    Planet* planet1 = new Planet(0.4, "planet1.png");
    Planet* planet2 = new Planet(0.6, "planet2.png");
    Planet* planet3 = new Planet(0.8, "planet3.png");
    Planet* planet5 = new Planet(2.0, "planet5.png");
    Planet* planet6 = new Planet(1.5, "planet6.png");
    Orbit* orbit1 = new Orbit(planet1, 20, 0.7, 0.56);
    Orbit* orbit2 = new Orbit(planet2, 25, 0.5);
    Orbit* orbit3 = new Orbit(planet3, 30, 0.3, 1.5);
    Orbit* orbit5 = new Orbit(planet5, 40, 0.1, 3*M_PI/2);
    Orbit* orbit6 = new Orbit(planet6, 45, 0.08, 3*M_PI/4);
    m_planetarySystem->AddOrbit(orbit1);
    m_planetarySystem->AddOrbit(orbit2);
    m_planetarySystem->AddOrbit(orbit3);
    m_planetarySystem->AddOrbit(orbit5);
    m_planetarySystem->AddOrbit(orbit6);

    layer.Add(sun);
    layer.Add(planet1);
    layer.Add(planet2);
    layer.Add(planet3);
    layer.Add(planet5);
    layer.Add(planet6);
    layer.Add(orbit1);
    layer.Add(orbit2);
    layer.Add(orbit3);
    layer.Add(orbit5);
    layer.Add(orbit6);
    layer.Add(m_planetarySystem);

    m_cameraControll = Unique<CameraControll>(new NumericCamControll());
    Camera* camera1 = new PerspectiveCamera(M_PI_2, 0.1f, 100.0f);
    StaticCamera* statCamera = new StaticCamera(camera1, &layer);
    statCamera->GetTransform().pos = glm::vec3(10.7304, 29.8384, 21.7261);
    statCamera->SideRotation() = 0.459837;
    statCamera->UpRotation() = -0.939478;
    
    Camera* camera2 = new PerspectiveCamera(M_PI_2, 0.1f, 100.0f);
    MovableCamera* movCamera = new MovableCamera(camera2, &layer);
    movCamera->GetTransform().pos = glm::vec3(10.7304, 29.8384, 21.7261);
    movCamera->SideRotation() = 0.459837;
    movCamera->UpRotation() = -0.939478;
    movCamera->MoveSpeed() = 10;
    m_cameraControll->AddController(statCamera);
    m_cameraControll->AddController(movCamera);
    layer.Add(camera1);
    layer.Add(camera2);
    layer.Add(statCamera);
    layer.Add(movCamera);
    statCamera->Activate();
}
void App::Update(float deltaTime)
{
}

void App::OnMouseEnter(const MouseEnterEvent& event)
{
    MousePos pos = Input::GetMousePos();
    //std::cout << "Mouse in window: " << event.entered << ", pos:" << pos.x << "," << pos.y << std::endl;
}

void App::OnKeyPressed(const KeyEvent& event)
{
    if(event.key == 'o') {
        Engine::Exit();
    } else if(event.key == ' ' && event.pressed) {
        if(m_stoped) {
            m_planetarySystemTimeGroup->Speed() = 1;
        } else {
            m_planetarySystemTimeGroup->Speed() = 0;
        }
        m_stoped = !m_stoped;
    }
}

void App::OnSpecialKeyPressed(const SpecialKeyEvent& event)
{

}

}
