#include "Rectangle.hpp"

namespace sadekpet {

Rectangle::Rectangle() :
    m_vertices{ 
        {glm::vec2( 0.5f,-0.5f)},
        {glm::vec2( 0.5f, 0.5f)}, 
        {glm::vec2(-0.5f, 0.5f)},
        {glm::vec2(-0.5f,-0.5f)}
    },
    m_indices{0, 1, 2, 0, 2, 3}
{
    m_vertexBuffer = Unique<VertexBuffer<Vec2D>>(VertexBuffer<Vec2D>::Create(4*sizeof(Vec2D), m_vertices));
    m_indexBuffer = Unique<IndexBuffer>(IndexBuffer::Create(6*sizeof(int), m_indices));
    VertexArray* vertexArray = new VertexArray();
    vertexArray->SetIndexBuffer(m_indexBuffer);
    vertexArray->AddVertexBuffer(m_vertexBuffer);
    m_vertexArray = Unique<VertexArray>(vertexArray);
    m_vertexArray->UnBind();
    m_indexBuffer->UnBind();
    m_vertexBuffer->UnBind();
}

void RectangleUniforms::SetUniformsImpl(int programID)
{
    Set(programID, m_color);
}
void RectangleUniforms::UpdateImpl()
{
}

TypeIndex RectangleShaderContext::GetType() const
{
    return TypeIndex(typeid(RectangleShaderContext));
}
const Shared<Primitives>& RectangleShaderContext::GetPrimitives()
{
    return m_rectangle;
}
Uniforms& RectangleShaderContext::GetUniforms()
{
    return m_uniforms;
}
TextureUnits& RectangleShaderContext::GetTextureUnits()
{
    return m_textureUnits;
}

}