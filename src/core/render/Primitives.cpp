#include "Primitives.hpp"

namespace sadekpet {

Mesh2D::Mesh2D(int vertexCount, int indicesCount, glm::vec2* vertices, glm::vec2* uvs, int* indices)
    : m_indicesCount(indicesCount)
{
    m_vericesBuffer = Unique<VertexBuffer<Vec2D>>(VertexBuffer<Vec2D>::Create(vertexCount*sizeof(Vec2D), (Vec2D*)vertices));
    m_uvsBuffer = Unique<VertexBuffer<Vec2D>>(VertexBuffer<Vec2D>::Create(vertexCount*sizeof(Vec2D), (Vec2D*)uvs));
    m_indicesBuffer = Unique<IndexBuffer>(IndexBuffer::Create(indicesCount*sizeof(uint), indices));
    VertexArray* vertexArray = new VertexArray();
    vertexArray->SetIndexBuffer(m_indicesBuffer);
    vertexArray->AddVertexBuffer(m_vericesBuffer);
    vertexArray->AddVertexBuffer(m_uvsBuffer);
    m_vertexArray = Unique<VertexArray>(vertexArray);
    m_vertexArray->UnBind();
    m_indicesBuffer->UnBind();
    m_vericesBuffer->UnBind();
}

BasicMesh2D::BasicMesh2D(int vertexCount, int indicesCount, glm::vec2* vertices, int* indices)
    : m_indicesCount(indicesCount)
{
    m_vericesBuffer = Unique<VertexBuffer<Vec2D>>(VertexBuffer<Vec2D>::Create(vertexCount*sizeof(Vec2D), (Vec2D*)vertices));
    m_indicesBuffer = Unique<IndexBuffer>(IndexBuffer::Create(indicesCount*sizeof(uint), indices));
    VertexArray* vertexArray = new VertexArray();
    vertexArray->SetIndexBuffer(m_indicesBuffer);
    vertexArray->AddVertexBuffer(m_vericesBuffer);
    m_vertexArray = Unique<VertexArray>(vertexArray);
    m_vertexArray->UnBind();
    m_indicesBuffer->UnBind();
    m_vericesBuffer->UnBind();
}

Mesh3D::Mesh3D(int vertexCount, int indicesCount, glm::vec3* vertices, glm::vec2* uvs, glm::vec3* normals, int* indices)
    : m_indicesCount(indicesCount)
{
    m_vericesBuffer = Unique<VertexBuffer<Vec3D>>(VertexBuffer<Vec3D>::Create(vertexCount*sizeof(Vec3D), (Vec3D*)vertices));
    m_uvsBuffer = Unique<VertexBuffer<Vec2D>>(VertexBuffer<Vec2D>::Create(vertexCount*sizeof(Vec2D), (Vec2D*)uvs));
    m_normalsBuffer = Unique<VertexBuffer<Vec3D>>(VertexBuffer<Vec3D>::Create(vertexCount*sizeof(Vec3D), (Vec3D*)normals));
    m_indicesBuffer = Unique<IndexBuffer>(IndexBuffer::Create(indicesCount*sizeof(uint), indices));
    VertexArray* vertexArray = new VertexArray();
    vertexArray->SetIndexBuffer(m_indicesBuffer);
    vertexArray->AddVertexBuffer(m_vericesBuffer);
    vertexArray->AddVertexBuffer(m_uvsBuffer);
    vertexArray->AddVertexBuffer(m_normalsBuffer);
    m_vertexArray = Unique<VertexArray>(vertexArray);
    m_vertexArray->UnBind();
    m_indicesBuffer->UnBind();
    m_vericesBuffer->UnBind();
}

BasicMesh3D::BasicMesh3D(int vertexCount, int indicesCount, glm::vec3* vertices, int* indices)
    : m_indicesCount(indicesCount)
{
    m_vericesBuffer = Unique<VertexBuffer<Vec3D>>(VertexBuffer<Vec3D>::Create(vertexCount*sizeof(Vec3D), (Vec3D*)vertices));
    m_indicesBuffer = Unique<IndexBuffer>(IndexBuffer::Create(indicesCount*sizeof(uint), indices));
    VertexArray* vertexArray = new VertexArray();
    vertexArray->SetIndexBuffer(m_indicesBuffer);
    vertexArray->AddVertexBuffer(m_vericesBuffer);
    m_vertexArray = Unique<VertexArray>(vertexArray);
    m_vertexArray->UnBind();
    m_indicesBuffer->UnBind();
    m_vericesBuffer->UnBind();
}

Line3D::Line3D(int vertexCount, int indicesCount, glm::vec3* vertices, int* indices)
    : m_indicesCount(indicesCount)
{
    m_vericesBuffer = Unique<VertexBuffer<Vec3D>>(VertexBuffer<Vec3D>::Create(vertexCount*sizeof(Vec3D), (Vec3D*)vertices));
    m_indicesBuffer = Unique<IndexBuffer>(IndexBuffer::Create(indicesCount*sizeof(uint), indices));
    VertexArray* vertexArray = new VertexArray();
    vertexArray->SetIndexBuffer(m_indicesBuffer);
    vertexArray->AddVertexBuffer(m_vericesBuffer);
    m_vertexArray = Unique<VertexArray>(vertexArray);
    m_vertexArray->UnBind();
    m_indicesBuffer->UnBind();
    m_vericesBuffer->UnBind();
}

}