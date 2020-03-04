/**
 * @file Primitives.hpp
 * @author sadekpet
 * @brief 
 */

#ifndef PGR_PRIMITIVES_HPP
#define PGR_PRIMITIVES_HPP

#include "VertexArray.hpp"
#include "VertexTypes.hpp"

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

class Primitives
{
public:
    virtual const Shared<VertexArray>& GetVertexArray() = 0;
    virtual PrimitiveType GetType() const = 0;
    virtual int GetCount() const = 0;
};

class Mesh2D : public Primitives
{
protected:
    Shared<VertexBuffer<Vec2D>> m_vericesBuffer;
    Shared<VertexBuffer<Vec2D>> m_uvsBuffer;
    Shared<IndexBuffer> m_indicesBuffer;
    Shared<VertexArray> m_vertexArray;
    int m_indicesCount;
public:
    Mesh2D(int vertexCount, int indicesCount, Vec2D* vertices, Vec2D* uvs, int* indices);
    virtual const Shared<VertexArray>& GetVertexArray() override { return m_vertexArray; }
    virtual PrimitiveType GetType() const override { return PrimitiveType::TRIANGLES; }
    virtual int GetCount() const override { return m_indicesCount; }
};

class Mesh3D : public Primitives
{
protected:
    Shared<VertexBuffer<Vec3D>> m_vericesBuffer;
    Shared<VertexBuffer<Vec2D>> m_uvsBuffer;
    Shared<VertexBuffer<Vec3D>> m_normalsBuffer;
    Shared<IndexBuffer> m_indicesBuffer;
    Shared<VertexArray> m_vertexArray;
    int m_indicesCount;
public:
    Mesh3D(int vertexCount, int indicesCount, Vec3D* vertices, Vec2D* uvs, Vec3D* normals, int* indices);
    virtual const Shared<VertexArray>& GetVertexArray() override { return m_vertexArray; }
    virtual PrimitiveType GetType() const override { return PrimitiveType::TRIANGLES; }
    virtual int GetCount() const override { return m_indicesCount; }
};

class Line3D : public Primitives
{
protected:
    Shared<VertexBuffer<Vec3D>> m_vericesBuffer;
    Shared<IndexBuffer> m_indicesBuffer;
    Shared<VertexArray> m_vertexArray;
    int m_indicesCount;
public:
    Line3D(int vertexCount, int indicesCount, Vec3D* vertices, int* indices);
    virtual const Shared<VertexArray>& GetVertexArray() override { return m_vertexArray; }
    virtual PrimitiveType GetType() const override { return PrimitiveType::LINES; }
    virtual int GetCount() const override { return m_indicesCount; }
};

}

#endif // PGR_PRIMITIVES_HPP