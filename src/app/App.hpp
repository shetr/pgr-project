/**
 * @file App.hpp
 * @author sadekpet
 * @brief 
 */

#ifndef PGR_APP_HPP
#define PGR_APP_HPP

#include <core/Input.hpp>

namespace sadekpet { 

class TimeGroup;
class RectangleNode;
class PlanetarySystem;
class CameraControll;
class PickPlanetController;
class Config;

/**
 * @brief Hlavní třída starající se o běh aplikace, její metody jsou volány třídou Engine. 
 * Obsahuje hlavně inicializaci aplikace a grafu scény.
 */
class App
{
    using MouseEnterHandler = ScopedEventHandler<MouseEnterEvent, App>;
    using KeyEventHandler = ScopedEventHandler<KeyEvent, App>;
    using SpecialKeyEventHandler = ScopedEventHandler<SpecialKeyEvent, App>;
private:
    Unique<MouseEnterHandler> m_mouseEnterHandler;
    Unique<KeyEventHandler> m_keyEventHandler;
    Unique<SpecialKeyEventHandler> m_specialKeyEventHandler;
    PlanetarySystem* m_planetarySystem;
    Shared<TimeGroup> m_planetarySystemTimeGroup;
    Shared<CameraControll> m_cameraControll;
    Unique<PickPlanetController> m_pickPlanetController;
    Unique<Config> m_config;
    bool m_useFog = false;
public:
    App();
    ~App();

    void Init();
    void Update(float deltaTime);

    void OnMouseEnter(const MouseEnterEvent& event);
    void OnKeyPressed(const KeyEvent& event);
    void OnSpecialKeyPressed(const SpecialKeyEvent& event);
private:

};

}

#endif // PGR_APP_HPP
