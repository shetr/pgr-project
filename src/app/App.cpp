#include "App.hpp"

#include <iostream>

#include <core/manage/ShaderManager.hpp>
#include <core/ui/Rectangle.hpp>
#include <core/scene/Layers.hpp>
#include <core/scene/Camera.hpp>

namespace sadekpet {

App::App()
{}
App::~App()
{}

void App::Init()
{
    m_mouseEnterHandler = std::make_unique<MouseEnterHandler>(this, &App::OnMouseEnter, Input::Get());
    m_keyEventHandler = std::make_unique<KeyEventHandler>(this, &App::OnKeyPressed, Input::Get());
    ShaderManager::AddRenderProgram(TypeIndex(typeid(RectangleMaterial)), "rectangle");
    Layer& layer = Layers::Get(Layers::Add("2D"));
    m_rectangle = new RectangleNode();
    layer.Add(m_rectangle);
    Camera* camera = new PerspectiveCamera(M_PI_2, 0.1f, 100.0f);
    layer.SetCurrentCamera(camera);
    layer.Add(camera);
}
void App::Update(float deltaTime)
{
    float speed = 1.0f;
    m_rectangle->GetTransform().rotAngle += deltaTime * speed;
}

void App::OnMouseEnter(const MouseEnterEvent& event)
{
    //std::cout << "Mouse in window: " << event.entered << std::endl;
}

void App::OnKeyPressed(const KeyEvent& event)
{
    if(event.key == 'a') {
        std::cout << "a " << event.pressed << std::endl;
    }
}

}
