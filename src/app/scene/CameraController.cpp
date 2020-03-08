#include "CameraController.hpp"


namespace sadekpet {

CameraController::CameraController(Camera* camera, Layer* layer)
    : m_camera(camera), m_layer(layer), m_active(false)
{
    ConnectChild(m_camera); 
}

void CameraController::Activate() 
{ 
    m_active = true;
    m_layer->SetCurrentCamera(m_camera);
}
void CameraController::Deactivate()
{ 
    m_active = false; 
}

void CameraControll::Set(size_t i)
{
    m_controllers[m_active]->Deactivate();
    m_controllers[m_active = i]->Activate();
}
void CameraControll::Next()
{
    Set((m_active + 1) % ControllerCount());
}

NumericCamControll::NumericCamControll() 
{
    m_keyEventHandler = std::make_unique<KeyEventHandler>(this, &NumericCamControll::OnKeyPressed, Input::Get());
}

void NumericCamControll::OnKeyPressed(const KeyEvent& event)
{
    if(event.pressed){
        size_t i = '1' - event.key;
        if(i >= 0 && i < ControllerCount()) {
            Set(i);
        } else if (event.key == 'n') {
            Next();
        }
    }
}

}