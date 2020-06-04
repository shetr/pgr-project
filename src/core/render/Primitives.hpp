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

/**
 * @brief Typ primitiva.
 */
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

/**
 * @brief Rodičovská třída pro všechny typy listů primitiv - trojúhleníky, úsečky, body.
 */
class Primitives
{
protected:
    Unique<VertexArray> m_vertexArray;
public:
    virtual void Bind() const { m_vertexArray->Bind(); }
    virtual PrimitiveType GetType() const = 0;
    virtual int GetCount() const = 0;
};

/**
 * @brief Množina dvourozměrných trojúhelníků. Obsahuje pozice a souřadnice textury.
 */
class Mesh2D : public Primitives
{
protected:
    Unique<VertexBuffer<Vec2D>> m_vericesBuffer;
    Unique<VertexBuffer<Vec2D>> m_uvsBuffer;
    Unique<IndexBuffer> m_indicesBuffer;
    int m_indicesCount;
public:
    Mesh2D(int vertexCount, int indicesCount, glm::vec2* vertices, glm::vec2* uvs, int* indices);
    virtual PrimitiveType GetType() const override { return PrimitiveType::TRIANGLES; }
    virtual int GetCount() const override { return m_indicesCount; }
};

/**
 * @brief Množina dvourozměrných trojúhelníků. Obsahuje pozice.
 */
class BasicMesh2D : public Primitives
{
protected:
    Unique<VertexBuffer<Vec2D>> m_vericesBuffer;
    Unique<IndexBuffer> m_indicesBuffer;
    int m_indicesCount;
public:
    BasicMesh2D(int vertexCount, int indicesCount, glm::vec2* vertices, int* indices);
    virtual PrimitiveType GetType() const override { return PrimitiveType::TRIANGLES; }
    virtual int GetCount() const override { return m_indicesCount; }
};

/**
 * @brief Množina trojrozměrných trojúhelníků. Obsahuje pozice, souřadnice textury, normály.
 */
class Mesh3D : public Primitives
{
protected:
    Unique<VertexBuffer<Vec3D>> m_vericesBuffer;
    Unique<VertexBuffer<Vec2D>> m_uvsBuffer;
    Unique<VertexBuffer<Vec3D>> m_normalsBuffer;
    Unique<IndexBuffer> m_indicesBuffer;
    int m_indicesCount;
public:
    Mesh3D(int vertexCount, int indicesCount, glm::vec3* vertices, glm::vec2* uvs, glm::vec3* normals, int* indices);
    virtual PrimitiveType GetType() const override { return PrimitiveType::TRIANGLES; }
    virtual int GetCount() const override { return m_indicesCount; }
};

/**
 * @brief Množina trojrozměrných trojúhelníků. Obsahuje pozice.
 */
class BasicMesh3D : public Primitives
{
protected:
    Unique<VertexBuffer<Vec3D>> m_vericesBuffer;
    Unique<IndexBuffer> m_indicesBuffer;
    int m_indicesCount;
public:
    BasicMesh3D(int vertexCount, int indicesCount, glm::vec3* vertices, int* indices);
    virtual PrimitiveType GetType() const override { return PrimitiveType::TRIANGLES; }
    virtual int GetCount() const override { return m_indicesCount; }
};

/**
 * @brief Množina trojrozměrných úseček. Obsahuje pozice.
 */
class Line3D : public Primitives
{
protected:
    Unique<VertexBuffer<Vec3D>> m_vericesBuffer;
    Unique<IndexBuffer> m_indicesBuffer;
    int m_indicesCount;
public:
    Line3D(int vertexCount, int indicesCount, glm::vec3* vertices, int* indices);
    virtual PrimitiveType GetType() const override { return PrimitiveType::LINES; }
    virtual int GetCount() const override { return m_indicesCount; }
};

}

#endif // PGR_PRIMITIVES_HPP