/**
 * @file Input.hpp
 * @author sadekpet
 * @brief 
 * 
 */

#ifndef PGR_INPUT_HPP
#define PGR_INPUT_HPP

#include "types.hpp"
#include "EventSystem.hpp"

namespace sadekpet {

using Key = unsigned char;

enum class SpecialKey : int
{
    F1 = 0x0001,
    F2 = 0x0002,
    F3 = 0x0003,
    F4 = 0x0004,
    F5 = 0x0005,
    F6 = 0x0006,
    F7 = 0x0007,
    F8 = 0x0008,
    F9 = 0x0009,
    F10 = 0x000A,
    F11 = 0x000B,
    F12 = 0x000C,
    LEFT = 0x0064,
    UP = 0x0065,
    RIGHT = 0x0066,
    DOWN = 0x0067,
    PAGE_UP = 0x0068,
    PAGE_DOWN = 0x0069,
    HOME = 0x006A,
    END = 0x006B,
    INSERT = 0x006C
};

#define PGR_SPECIAL_COUNT 21

enum class MouseButton : int
{
    LEFT = 0x0000,
    MIDDLE = 0x0001,
    RIGHT = 0x0002
};

#define PGR_MOUSE_BUTTON_COUNT 3

struct MousePos
{
    int x;
    int y;
};

struct KeyEvent
{
    Key key;
    bool pressed;
};

struct SpecialKeyEvent
{
    SpecialKey key;
    bool pressed;
};

struct MouseButtonEvent
{
    MouseButton button;
    bool pressed; // DOWN == false
};

struct MouseMoveEvent
{
    MousePos pos;
    bool someButtonPressed;
};

struct MouseWheelEvent
{
    int wheel;
    int dir;
};

struct MouseEnterEvent
{
    bool entered;
};

class Input :
    public IEventSystem<KeyEvent>,
    public IEventSystem<SpecialKeyEvent>,
    public IEventSystem<MouseButtonEvent>,
    public IEventSystem<MouseMoveEvent>,
    public IEventSystem<MouseWheelEvent>,
    public IEventSystem<MouseEnterEvent>
{
private:
    static Input s_input;
    static bool s_keyPressed[sizeof(Key)];
    static bool s_specialKeyPressed[PGR_SPECIAL_COUNT];
    static bool s_mouseButtonPressed[PGR_MOUSE_BUTTON_COUNT];
    static MousePos s_mousePos;
    static bool s_isCursorInWindow;
    EventSystem m_eventSystem;
public:
    static void Init();
    static Input* Get() { return &s_input; }

    static bool IsKeyPressed(Key key);
    static bool IsSpecialKeyPressed(SpecialKey key);
    static bool IsMouseButtonPressed(MouseButton button);
    static bool IsCursorInWindow();
    static MousePos GetMousePos();
    static void SetMousePos(const MousePos& pos);
    static void SetMousePosToCenter();
    static void HideCursor();
    static void ShowCursor();

    PGR_EVENT_ACTIONS(KeyEvent, m_eventSystem)
    PGR_EVENT_ACTIONS(SpecialKeyEvent, m_eventSystem)
    PGR_EVENT_ACTIONS(MouseButtonEvent, m_eventSystem)
    PGR_EVENT_ACTIONS(MouseMoveEvent, m_eventSystem)
    PGR_EVENT_ACTIONS(MouseWheelEvent, m_eventSystem)
    PGR_EVENT_ACTIONS(MouseEnterEvent, m_eventSystem)
private:
    static bool& KeyPressed(Key key);
    static bool& SpecialKeyPressed(SpecialKey key);
    static bool& MouseButtonPressed(MouseButton button);

    static void KeyboardCallback(unsigned char key, int x, int y);
    static void SpecialCallback(int key, int x, int y);
    static void KeyboardUpCallback(unsigned char key, int x, int y);
    static void SpecialUpCallback(int key, int x, int y);
    static void MouseCallback(int button, int state, int x, int y);
    static void MotionCallback(int x, int y);
    static void PassiveMotionCallback(int x, int y);
    static void MouseWheelCallback(int wheel, int dir, int x, int y);
    static void MouseEnterCallback(int state);
};

}

#endif // PGR_INPUT_HPP