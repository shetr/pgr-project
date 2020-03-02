/**
 * @file Mesh.hpp
 * @author sadekpet
 * @brief 
 */

#ifndef PGR_MESH_HPP
#define PGR_MESH_HPP

#include "VertexArray.hpp"

namespace sadekpet {

enum class PrimitiveType : uint
{
    POINTS = 0x0000,
    LINES = 0x0001,
    LINE_LOOP = 0x0002,
    LINE_STRIP = 0x0003,
    TRIANGLES = 0x0004,
    TRIANGLE_STRIP = 0x0005,
    TRIANGLE_FAN = 0x0006
};

class Mesh
{
public:
    virtual const Shared<VertexArray>& GetVertexArray() = 0;
    virtual PrimitiveType GetType() const = 0;
    virtual int GetCount() const = 0;
};

}

#endif // PGR_MESH_HPP