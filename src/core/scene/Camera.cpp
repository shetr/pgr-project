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

glm::vec3 PerspectiveCamera::GetMouseLookDir(float x, float y)
{
    WindowSize winSize = Window::Get()->GetSize();
    float xSize = 2*x / ((float) winSize.width) - 1;
    float ySize = 2*y / ((float) winSize.height) - 1;
    float yMax = m_near * glm::tan(m_fov / 2);
    float xMax = yMax * ((float)winSize.width) / ((float)winSize.height);
    float xFact = xSize * xMax;
    float yFact = ySize * yMax;
    glm::mat4 worldTrans = GetWorldTransform();
    glm::vec3 lookDir = glm::normalize(glm::vec3(worldTrans * glm::vec4(0,0,-1,0)));
    glm::vec3 sideDir = glm::normalize(glm::vec3(worldTrans * glm::vec4(-1,0,0,0)));
    glm::vec3 upDir = glm::cross(sideDir, lookDir);
    return glm::normalize(m_near*lookDir + xFact*sideDir + yFact*upDir);
}

void PerspectiveCamera::SetProjection()
{
    m_projection = glm::perspective(m_fov, GetAspectRatio(), m_near, m_far);
}

}