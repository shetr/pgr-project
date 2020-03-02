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

class App
{
    using MouseEnterHandler = ScopedEventHandler<MouseEnterEvent, App>;
    using KeyEventHandler = ScopedEventHandler<KeyEvent, App>;
private:
    Unique<MouseEnterHandler> m_mouseEnterHandler;
    Unique<KeyEventHandler> m_keyEventHandler;
    RectangleNode* m_rectangle;
public:
    App();
    ~App();

    void Init();
    void Update(float deltaTime);

    void OnMouseEnter(const MouseEnterEvent& event);
    void OnKeyPressed(const KeyEvent& event);
private:

};

}

#endif // PGR_APP_HPP
