#include "Input.hpp"

#include "render/OpenGL.hpp"

#include "Window.hpp"

namespace sadekpet {

Input Input::s_input{};
bool Input::s_keyPressed[256] = {false};
bool Input::s_specialKeyPressed[PGR_SPECIAL_COUNT] = {false};
bool Input::s_mouseButtonPressed[PGR_MOUSE_BUTTON_COUNT] = {false};
MousePos Input::s_mousePos = {0,0};
bool Input::s_isCursorInWindow = false;

void Input::Init()
{
    glutKeyboardFunc(&Input::KeyboardCallback);
    glutSpecialFunc(&Input::SpecialCallback);
    glutKeyboardUpFunc(&Input::KeyboardUpCallback);
    glutSpecialUpFunc(&Input::SpecialUpCallback);
    glutMouseFunc(&Input::MouseCallback);
    glutMotionFunc(&Input::MotionCallback);
    glutPassiveMotionFunc(&Input::PassiveMotionCallback);
    glutMouseWheelFunc(&Input::MouseWheelCallback);
    glutEntryFunc(&Input::MouseEnterCallback);
}
bool Input::IsKeyPressed(Key key)
{
    return KeyPressed(key);
}
bool Input::IsSpecialKeyPressed(SpecialKey key)
{
    return SpecialKeyPressed(key);
}
bool Input::IsMouseButtonPressed(MouseButton button)
{
    return MouseButtonPressed(button);
}
bool Input::IsCursorInWindow()
{
    return s_isCursorInWindow;
}
MousePos Input::GetMousePos()
{
    return s_mousePos;
}
void Input::SetMousePos(const MousePos& pos)
{
    s_mousePos = pos;
    glutWarpPointer(pos.x, pos.y);
}
void Input::SetMousePosToCenter()
{
    MousePos pos;
    WindowSize winSize = Window::GetSize();
    pos.x = winSize.width/2;
    pos.y = winSize.height/2;
    SetMousePos(pos);
}
void Input::HideCursor()
{
    glutSetCursor(GLUT_CURSOR_NONE);
}
void Input::ShowCursor()
{
    glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
}

uint8_t Input::GetStencilID(const MousePos& pos)
{
    uint8_t id;
    WindowSize winSize = Window::GetSize();
    GL(ReadPixels(pos.x, winSize.height - pos.y, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_BYTE, &id));
    return id;
}

void Input::StencilUpdate(float deltaTime)
{
    StencilUpdateEvent event{deltaTime};
    s_input.m_eventSystem.Execute(event);
}

bool& Input::KeyPressed(Key key)
{
    return s_keyPressed[key];
}
bool& Input::SpecialKeyPressed(SpecialKey key)
{
    int val = static_cast<int>(key);
    return s_specialKeyPressed[val < 0x0064 ? val - 0x0001 : 0x000C + val - 0x0064];
}
bool& Input::MouseButtonPressed(MouseButton button)
{
    return s_mouseButtonPressed[static_cast<int>(button)];
}

void Input::KeyboardCallback(unsigned char key, int x, int y)
{
    KeyPressed(key) = true;
    KeyEvent event{key, true};
    s_input.m_eventSystem.Execute(event);
}
void Input::SpecialCallback(int key, int x, int y)
{
    SpecialKey special = static_cast<SpecialKey>(key);
    SpecialKeyPressed(special) = true;
    SpecialKeyEvent event{special, true};
    s_input.m_eventSystem.Execute(event);
}
void Input::KeyboardUpCallback(unsigned char key, int x, int y)
{
    KeyPressed(key) = false;
    KeyEvent event{key, false};
    s_input.m_eventSystem.Execute(event);

}
void Input::SpecialUpCallback(int key, int x, int y)
{
    SpecialKey special = static_cast<SpecialKey>(key);
    SpecialKeyPressed(special) = false;
    SpecialKeyEvent event{special, false};
    s_input.m_eventSystem.Execute(event);
}
void Input::MouseCallback(int button, int state, int x, int y)
{
    MouseButtonEvent event{static_cast<MouseButton>(button), static_cast<bool>(state)};
    MouseButtonPressed(event.button) = event.pressed;
    s_input.m_eventSystem.Execute(event);
}
void Input::MotionCallback(int x, int y)
{
    s_mousePos = {x, y};
    MouseMoveEvent event{s_mousePos, true};
    s_input.m_eventSystem.Execute(event);
}
void Input::PassiveMotionCallback(int x, int y)
{
    s_mousePos = {x, y};
    MouseMoveEvent event{s_mousePos, false};
    s_input.m_eventSystem.Execute(event);
}
void Input::MouseWheelCallback(int wheel, int dir, int x, int y)
{
    MouseWheelEvent event{wheel, dir};
    s_input.m_eventSystem.Execute(event);
}
void Input::MouseEnterCallback(int state)
{
    s_isCursorInWindow = static_cast<bool>(state);
    MouseEnterEvent event{s_isCursorInWindow};
    s_input.m_eventSystem.Execute(event);
}

}