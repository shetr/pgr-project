#include "Camera.hpp"

#include <core/Window.hpp>
#include <glm/gtx/transform.hpp>

namespace sadekpet {

Set<Camera*> Camera::s_cameras;

float Camera::GetAspectRatio()
{
    WindowSize winSize = Window::Get()->GetSize();
    return ((float)winSize.width) / ((float)winSize.height);
}

PerspectiveCamera::PerspectiveCamera(float fov, float near, float far)
    : m_fov(fov), m_near(near), m_far(far)
{
    SetProjection();
}


void PerspectiveCamera::Resize()
{
    SetProjection();
}

void PerspectiveCamera::SetProjection()
{
    m_projection = glm::perspective(m_fov, GetAspectRatio(), m_near, m_far);
}

}