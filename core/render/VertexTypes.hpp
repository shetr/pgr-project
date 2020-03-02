/**
 * @file VertexTypes.hpp
 * @author sadekpet 
 * @brief 
 * 
 */

#ifndef PGR_VERTEX_TYPES_HPP
#define PGR_VERTEX_TYPES_HPP

#include <glm/glm.hpp>

namespace sadekpet {

class VertexLayout;

struct Vec2D
{
    glm::vec2 v;
private:
    static VertexLayout s_layout;
public:
    static const VertexLayout& GetLayout();
};

struct Vec3D
{
    glm::vec3 v;
private:
    static VertexLayout s_layout;
public:
    static const VertexLayout& GetLayout();
};

}

#endif // PGR_VERTEX_TYPES_HPP