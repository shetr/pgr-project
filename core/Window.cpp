#include "Window.hpp"

#include "render/OpenGL.hpp"

namespace sadekpet {

Window* Window::s_window = nullptr;

void Window::Init(WindowSize size, const char* title)
{
    if(s_window == nullptr) {
        s_window = new Window(size, title);
    }
}

Window::Window(WindowSize size, const char* title) : m_size(size)
{
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(m_size.width, m_size.height);
    m_id = glutCreateWindow(title);
    glutCloseFunc(&Window::CloseCallback);
    glutReshapeFunc(&Window::SizeCallback);
}

Window::~Window()
{
    glutDestroyWindow(m_id);
    s_window = nullptr;
}

void Window::SetSize(WindowSize size)
{
    s_window->m_size = size;
    glutReshapeWindow(size.width, size.height);
}

bool Window::IsFullScreen()
{
    return static_cast<bool>(glutGet(GLUT_FULL_SCREEN));
}

void EnterFullScreen()
{
    glutFullScreen();
}
void LeaveFullScreen()
{
    glutLeaveFullScreen();
}

void Window::CloseCallback()
{
    WindowCloseEvent event{s_window};
    s_window->m_eventSystem.Execute(event);
}

void Window::SizeCallback(int width, int height)
{
    s_window->m_size = {width, height};
    WindowSizeEvent event{s_window, s_window->m_size};
    s_window->m_eventSystem.Execute(event);
}


}