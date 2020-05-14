#include "App.hpp"

#include <iostream>

#include <core/Engine.hpp>
#include <core/Window.hpp>
#include <core/manage/ShaderManager.hpp>
#include <core/ui/Rectangle.hpp>
#include <core/scene/Layers.hpp>
#include <core/scene/Camera.hpp>
#include <app/scene/CameraController.hpp>
#include <app/scene/Sphere.hpp>

#include <app/scene/PlanetarySystem.hpp>
#include <app/scene/Planet.hpp>

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
    ShaderManager::AddRenderProgram(TypeIndex(typeid(SphereShaderContext)), "sphere");
    Layer& layer = Layers::Get(Layers::Add("3D"));

    m_rectangle = new RectangleNode();
    SphereNode* sphere = new SphereNode();
    m_rectangle->GetTransform().pos.x = 2;
    layer.Add(m_rectangle);
    /*RectangleNode* rect2 = new RectangleNode();
    rect2->GetTransform().pos.x = -2;
    layer.Add(rect2);
    layer.Add(sphere);*/

    Sun* sun = new Sun(1);
    m_planetarySystem = new PlanetarySystem(sun);
    Planet* planet = new Planet(0.5);
    Orbit* orbit = new Orbit(planet, 2);
    m_planetarySystem->AddOrbit(orbit);

    layer.Add(sun);
    layer.Add(planet);
    layer.Add(orbit);
    layer.Add(m_planetarySystem);


    Camera* camera = new PerspectiveCamera(M_PI_2, 0.1f, 100.0f);
    MovableCamera* movCamera = new MovableCamera(camera, &layer);
    movCamera->GetTransform().pos.z = 3;
    layer.Add(movCamera);
    movCamera->Activate();
}
void App::Update(float deltaTime)
{
    float speed = 1.0f;
    m_rectangle->GetTransform().rotAngle += deltaTime * speed;
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
    }
}

void App::OnSpecialKeyPressed(const SpecialKeyEvent& event)
{

}

}
