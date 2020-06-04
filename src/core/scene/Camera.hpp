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

/**
 * @brief Node reprezentující kameru s její projekční maticí + view maticí v potobě world transform nodu.
 */
class Camera : public Node
{
protected:
    static Set<Camera*> s_cameras;
    glm::mat4 m_projection;
public:
    Camera(const glm::mat4& projection = glm::mat4(1.0f)) 
        : m_projection(projection) { s_cameras.insert(this); }
    virtual ~Camera() { s_cameras.erase(this); }
    const glm::mat4& GetProjection() const { return m_projection; }

    virtual void Resize() = 0;
    virtual glm::vec3 GetMouseLookDir(float x, float y) = 0;

    static Set<Camera*>& Cameras() { return s_cameras; }

protected:
    float GetAspectRatio();
};

/**
 * @brief Perspektivní kamera.
 */
class PerspectiveCamera : public Camera 
{
protected:
    float m_fov;
    float m_near;
    float m_far;
public:
    PerspectiveCamera(float fov, float near, float far);

    virtual void Resize();
    glm::vec3 GetMouseLookDir(float x, float y);
protected:
    void SetProjection();
};

/*
class OrthographicCamera : public Camera 
{

};*/

}

#endif // PGR_CAMERA_HPP