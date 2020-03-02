#include "VertexArray.hpp"

#include "OpenGL.hpp"


namespace sadekpet
{

VertexArray::VertexArray()
{
    GL(GenVertexArrays(1, &m_id));
}
VertexArray::~VertexArray()
{
    GL(DeleteVertexArrays(1, &m_id));
}

void VertexArray::SetIndexBuffer(const Shared<IndexBuffer>& indexBuffer)
{
    Bind();
    indexBuffer->Bind();
    m_size = indexBuffer->GetSize();
}

void VertexArray::Bind() const
{
    GL(BindVertexArray(m_id));
}
void VertexArray::UnBind()
{
    GL(BindVertexArray(0));
}

void VertexArray::EnableVertexAttribArray(uint i)
{
    GL(EnableVertexAttribArray(i));
}
void VertexArray::VertexAttribPointer(uint i, int count, uint type, bool normalized, uint stride, const void* offset)
{
    GL(VertexAttribPointer(
        i,
        count,
        type,
        normalized,
        stride,
        offset
    ));
}

}