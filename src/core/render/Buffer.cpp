#include "Buffer.hpp"

#include "OpenGL.hpp"

namespace sadekpet
{

GraphicsBuffer::GraphicsBuffer(int size, const void* data, GraphicsBufferTarget target)
    : GraphicsBuffer(size, data, target, GraphicsBufferUsage::STATIC_DRAW)
{
}

GraphicsBuffer::GraphicsBuffer(int size, const void* data, GraphicsBufferTarget target, GraphicsBufferUsage usage)
    : m_size(size), m_data(data), m_usage(usage), m_target(target)
{
    GL(GenBuffers(1, &m_id));
}

GraphicsBuffer::~GraphicsBuffer()
{
    UnBind();
    GL(DeleteBuffers(1, &m_id));
}

void GraphicsBuffer::Bind()
{
    GL(BindBuffer(static_cast<uint32_t>(GetTarget()), m_id));
}

void GraphicsBuffer::UnBind()
{
    GL(BindBuffer(static_cast<uint32_t>(GetTarget()), 0));
}

void GraphicsBuffer::Init()
{
    GL(BufferData(static_cast<uint32_t>(GetTarget()), m_size, m_data, static_cast<uint32_t>(m_usage)));
}


void GraphicsBuffer::Update(int size, const void* data)
{
    glBufferSubData(static_cast<uint32_t>(GetTarget()), 0, size, data);
}

int VertexElement::TypeSize(VertexType type)
{
    switch (type)
    {
    case VertexType::INT8:
        return 1;
    case VertexType::UINT8:
        return 1;
    case VertexType::INT16:
        return 2;
    case VertexType::UINT16:
        return 2;
    case VertexType::INT32:
        return 4;
    case VertexType::UINT32:
        return 4;
    case VertexType::FLOAT16:
        return 2;
    case VertexType::FLOAT32:
        return 4;
    case VertexType::FLOAT64:
        return 8;
    case VertexType::FIXED:
        return 1;
    
    default:
        return 0;
    }
}

int VertexLayout::ByteSize() const
{
    int size = 0;
    for(const VertexElement& element : m_elements) {
        size += element.ByteSize();
    }
    return size;
}

IndexBuffer* IndexBuffer::Create(int count, const int* indices)
{
    IndexBuffer* buffer = new IndexBuffer(count, indices);
    buffer->Bind();
    buffer->Init();
    return buffer;
}
IndexBuffer* IndexBuffer::Create(int count, const int* indices, GraphicsBufferUsage usage)
{
    IndexBuffer* buffer = new IndexBuffer(count, indices, usage);
    buffer->Bind();
    buffer->Init();
    return buffer;
}

IndexBuffer* IndexBuffer::CreateDynamic(int count)
{
    IndexBuffer* buffer = new IndexBuffer(count, nullptr, GraphicsBufferUsage::STREAM_DRAW);
    buffer->Bind();
    buffer->Init();
    return buffer;
}
IndexBuffer* IndexBuffer::CreateDynamic(int count, int initCount, const int* initIndices)
{
    IndexBuffer* buffer = new IndexBuffer(count, nullptr, GraphicsBufferUsage::STREAM_DRAW);
    buffer->UpdateData(initCount, initIndices);
    return buffer;
}

void IndexBuffer::UpdateData(int count, const int* vertices)
{
    Bind();
    Init();
    Update(count*sizeof(int), vertices);
}

}