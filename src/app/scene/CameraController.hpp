/**
 * @file CameraController.hpp
 * @author sadekpet
 * @brief 
 * @date 2020-03-08
 * 
 */

#ifndef PGR_CAMERA_CONTROLLER_HPP
#define PGR_CAMERA_CONTROLLER_HPP

#include <core/scene/Camera.hpp>
#include <core/scene/Layers.hpp>
#include <core/Input.hpp>

namespace sadekpet {

class CameraController : public Node
{
private:
    Camera* m_camera;
    Layer* m_layer;
    bool m_active;
public:
    CameraController(Camera* camera, Layer* layer);
    bool IsActive() const { return m_active; }
    void Activate();
    void Deactivate();
    Camera* GetCamera() { return m_camera; }
};

class CameraControll
{
private:
    Vector<CameraController*> m_controllers;
    size_t m_active = 0;
public:
    CameraControll() {}
    void AddController(CameraController* controller) { m_controllers.push_back(controller); }
    size_t ControllerCount() { return m_controllers.size(); }
    void Set(size_t i);
    void Next();
};

class NumericCamControll : public CameraControll
{
    using KeyEventHandler = ScopedEventHandler<KeyEvent, NumericCamControll>;
private:
    Unique<KeyEventHandler> m_keyEventHandler;
public:
    NumericCamControll();
    void OnKeyPressed(const KeyEvent& event);
};

using StaticCamera = CameraController;

class MovingCamera : public CameraController
{

};

class MovableCamera : public CameraController
{
private:
    float m_moveSpeed = 0.5f;
    float m_turnSpeed = 0.5f;
public:
    MovableCamera(Camera* camera, Layer* layer);
    float& MoveSpeed() { return m_moveSpeed; }
    float& TurnSpeed() { return m_turnSpeed; }
    void Update(float deltaTime) override;
};

}

#endif // PGR_CAMERA_CONTROLLER_HPP