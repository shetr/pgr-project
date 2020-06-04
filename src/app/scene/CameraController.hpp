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

/**
 * @brief Nadřazená třída pro ovládání kamery - např statická, pohyblivá.
 */
class CameraController : public Node
{
private:
    Camera* m_camera;
    Vector<Layer*> m_layers;
    bool m_active;
public:
    CameraController(Camera* camera);
    float& SideRotation() { return m_transform.rotAngle; }
    float& UpRotation() { return GetCamera()->GetTransform().rotAngle; }
    void AddLayer(Layer* layer);
    bool IsActive() const { return m_active; }
    void Activate();
    void Activate(CameraController* prevController);
    void Deactivate();
    Camera* GetCamera() { return m_camera; }
protected:
    virtual void OnActivate() {} 
    virtual void OnActivate(CameraController* prevController) { OnActivate(); }
    virtual void OnDeactivate() {} 
};

/**
 * @brief Stará se o přepínání mezi kamerami.
 */
class CameraControll
{
private:
    Vector<CameraController*> m_controllers;
    size_t m_active = 0;
public:
    CameraControll() {}
    void AddController(CameraController* controller) { m_controllers.push_back(controller); }
    size_t ControllerCount() { return m_controllers.size(); }
    CameraController* GetActive() { return m_controllers[m_active]; }
    void Set(size_t i);
    void Next();
};

/**
 * @brief Přepínání mezi kamerami pomocí čísel na klávesnici.
 */
class NumericCamControll : public CameraControll
{
    using KeyEventHandler = ScopedEventHandler<KeyEvent, NumericCamControll>;
private:
    Unique<KeyEventHandler> m_keyEventHandler;
public:
    NumericCamControll();
    void OnKeyPressed(const KeyEvent& event);
};

/**
 * @brief Statická kamera.
 */
using StaticCamera = CameraController;

/**
 * @brief Pohyblivá kamera.
 */
class MovableCamera : public CameraController
{
    using MouseMoveHandler = ScopedEventHandler<MouseMoveEvent, MovableCamera>;
    using KeyEventHandler = ScopedEventHandler<KeyEvent, MovableCamera>;
private:
    float m_moveSpeed = 2.0f;
    float m_turnSpeed = 0.1f;
    glm::vec2 m_actualDir = glm::vec2(0,0);
    glm::vec2 m_prevDir = glm::vec2(0,0);
    glm::vec2 m_nextDir = glm::vec2(0,0);
    float m_lerpSteps = 5;
    float m_lerpStep = 1;
    Unique<MouseMoveHandler> m_mouseMoveHandler;
    Unique<KeyEventHandler> m_keyEventHandler;
public:
    MovableCamera(Camera* camera);
    float& MoveSpeed() { return m_moveSpeed; }
    float& TurnSpeed() { return m_turnSpeed; }
    void Update(float deltaTime) override;
    void OnMouseEvent(const MouseMoveEvent& event);
    void OnKeyPressed(const KeyEvent& event);
protected:
    void OnActivate() override;
    void OnActivate(CameraController* prevController) override;
    void OnDeactivate() override;
private:
    void LerpStep();
};

}

#endif // PGR_CAMERA_CONTROLLER_HPP