#include "Primitives.hpp"

namespace sadekpet {

Mesh2D::Mesh2D(int vertexCount, int indicesCount, Vec2D* vertices, Vec2D* uvs, int* indices)
    : m_indicesCount(indicesCount)
{
    m_vericesBuffer = Shared<VertexBuffer<Vec2D>>(VertexBuffer<Vec2D>::Create(vertexCount*sizeof(Vec2D), vertices));
    m_uvsBuffer = Shared<VertexBuffer<Vec2D>>(VertexBuffer<Vec2D>::Create(vertexCount*sizeof(Vec2D), uvs));
    m_indicesBuffer = Shared<IndexBuffer>(IndexBuffer::Create(indicesCount*sizeof(uint), indices));
    VertexArray* vertexArray = new VertexArray();
    vertexArray->SetIndexBuffer(m_indicesBuffer);
    vertexArray->AddVertexBuffer(m_vericesBuffer);
    vertexArray->AddVertexBuffer(m_uvsBuffer);
    m_vertexArray = Shared<VertexArray>(vertexArray);
}

Mesh3D::Mesh3D(int vertexCount, int indicesCount, Vec3D* vertices, Vec2D* uvs, Vec3D* normals, int* indices)
    : m_indicesCount(indicesCount)
{
    m_vericesBuffer = Shared<VertexBuffer<Vec3D>>(VertexBuffer<Vec3D>::Create(vertexCount*sizeof(Vec3D), vertices));
    m_uvsBuffer = Shared<VertexBuffer<Vec2D>>(VertexBuffer<Vec2D>::Create(vertexCount*sizeof(Vec2D), uvs));
    m_normalsBuffer = Shared<VertexBuffer<Vec3D>>(VertexBuffer<Vec3D>::Create(vertexCount*sizeof(Vec3D), normals));
    m_indicesBuffer = Shared<IndexBuffer>(IndexBuffer::Create(indicesCount*sizeof(uint), indices));
    VertexArray* vertexArray = new VertexArray();
    vertexArray->SetIndexBuffer(m_indicesBuffer);
    vertexArray->AddVertexBuffer(m_vericesBuffer);
    vertexArray->AddVertexBuffer(m_uvsBuffer);
    vertexArray->AddVertexBuffer(m_normalsBuffer);
    m_vertexArray = Shared<VertexArray>(vertexArray);
}

Line3D::Line3D(int vertexCount, int indicesCount, Vec3D* vertices, int* indices)
    : m_indicesCount(indicesCount)
{
    m_vericesBuffer = Shared<VertexBuffer<Vec3D>>(VertexBuffer<Vec3D>::Create(vertexCount*sizeof(Vec3D), vertices));
    m_indicesBuffer = Shared<IndexBuffer>(IndexBuffer::Create(indicesCount*sizeof(uint), indices));
    VertexArray* vertexArray = new VertexArray();
    vertexArray->SetIndexBuffer(m_indicesBuffer);
    vertexArray->AddVertexBuffer(m_vericesBuffer);
    m_vertexArray = Shared<VertexArray>(vertexArray);
}

}