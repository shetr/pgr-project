/**
 * @file App.hpp
 * @author sadekpet
 * @brief 
 * 
 */

#ifndef PGR_APP_HPP
#define PGR_APP_HPP

#include <core/Input.hpp>

namespace sadekpet { 

class RectangleNode;
class PlanetarySystem;

class App
{
    using MouseEnterHandler = ScopedEventHandler<MouseEnterEvent, App>;
    using KeyEventHandler = ScopedEventHandler<KeyEvent, App>;
    using SpecialKeyEventHandler = ScopedEventHandler<SpecialKeyEvent, App>;
private:
    Unique<MouseEnterHandler> m_mouseEnterHandler;
    Unique<KeyEventHandler> m_keyEventHandler;
    Unique<SpecialKeyEventHandler> m_specialKeyEventHandler;
    RectangleNode* m_rectangle;
    PlanetarySystem* m_planetarySystem;
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
