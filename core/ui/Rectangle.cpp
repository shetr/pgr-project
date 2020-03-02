#include "Rectangle.hpp"

namespace sadekpet {

Rectangle::Rectangle() :
    m_vertices{ 
        {glm::vec2(-0.5f,-0.5f)}, 
        {glm::vec2(-0.5f, 0.5f)}, 
        {glm::vec2( 0.5f, 0.5f)}, 
        {glm::vec2( 0.5f,-0.5f)}
    },
    m_indices{0, 1, 2, 0, 2, 3}
{
    m_vertexBuffer = Shared<VertexBuffer<Vec2D>>(VertexBuffer<Vec2D>::Create(4*sizeof(Vec2D), m_vertices));
    m_indexBuffer = Shared<IndexBuffer>(IndexBuffer::Create(6*sizeof(int), m_indices));
    VertexArray* vertexArray = new VertexArray();
    vertexArray->SetIndexBuffer(m_indexBuffer);
    vertexArray->AddVertexBuffer(m_vertexBuffer);
    m_vertexArray = Shared<VertexArray>(vertexArray);
}

void RectangleUniforms::SetUniformsImpl(int programID)
{
    Set(programID, m_color);
}
void RectangleUniforms::UpdateImpl()
{
}

TypeIndex RectangleMaterial::GetType() const
{
    return TypeIndex(typeid(RectangleMaterial));
}
Mesh& RectangleMaterial::GetMesh()
{
    return m_rectangle;
}
Uniforms& RectangleMaterial::GetUniforms()
{
    return m_uniforms;
}
TextureUnits& RectangleMaterial::GetTextureUnits()
{
    return m_textureUnits;
}

}