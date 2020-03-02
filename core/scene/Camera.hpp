/**
 * @file Camera.hpp
 * @author sadekpet 
 * @brief 
 * @date 2020-03-01
 * 
 */

#ifndef PGR_CAMERA_HPP
#define PGR_CAMERA_HPP

#include <core/scene/Node.hpp>

namespace sadekpet {

class Camera : public Node
{
private:
    static Camera* s_current;
    glm::mat4 m_projection;
public:
    Camera(const glm::mat4& projection) : m_projection(projection) {}
    const glm::mat4& GetProjection() const { return m_projection; }

    static Camera* GetCurrent() { return s_current; }
    static void SetCurrent(Camera* c) { s_current = c; } 
};

}

#endif // PGR_CAMERA_HPP