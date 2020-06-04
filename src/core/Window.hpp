/**
 * @file Window.hpp
 * @author sadekpet 
 * @brief 
 * 
 */

#ifndef PGR_WINDOW_HPP
#define PGR_WINDOW_HPP

#include "EventSystem.hpp"

namespace sadekpet {

class Window;

/**
 * @brief Velikost okna v pixelech.
 */
struct WindowSize
{
    int width; 
    int height;
};

/**
 * @brief Událost při zavření okna.
 */
struct WindowCloseEvent
{
    Window* window;
};

/**
 * @brief Událost při změně velikosti okna.
 */
struct WindowSizeEvent
{
    Window* window;
    WindowSize size;
};

/**
 * @brief Stará se o vytvoření, inicializaci a vyvolávání událostí okana.
 */
class Window :
    public IEventSystem<WindowCloseEvent>,
    public IEventSystem<WindowSizeEvent>
{
private:
    int m_id;
    WindowSize m_size;
    EventSystem m_eventSystem;
    static Window* s_window;
public:
    static void Init(WindowSize size, const char* title);
    static Window* Get() { return s_window; }
    ~Window();

    static int GetID() { return s_window->m_id; }
    static WindowSize GetSize() { return s_window->m_size; }
    static void SetSize(WindowSize size);
    static bool IsFullScreen();

    static void EnterFullScreen();
    static void LeaveFullScreen();

    static void Show();
    static void Hide();

    PGR_EVENT_ACTIONS(WindowCloseEvent, m_eventSystem)
    PGR_EVENT_ACTIONS(WindowSizeEvent, m_eventSystem)
private:
    Window(WindowSize size, const char* title);

    static void CloseCallback();
    static void SizeCallback(int width, int height);

};

}

#endif // PGR_WINDOW_HPP