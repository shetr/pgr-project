#include "BufferManager.hpp"

namespace sadekpet {

BufferManager* BufferManager::s_instance = nullptr;

BufferManager* BufferManager::Init()
{
    if(s_instance == nullptr) {
        s_instance = new BufferManager;
    }
    return s_instance;
}
void BufferManager::AddGraphicsBuffer(GraphicsBuffer* buffer)
{
    s_instance->m_buffers[buffer->GetID()] = Unique<GraphicsBuffer>(buffer);
}
void BufferManager::AddVertexArray(VertexArray* array)
{
    s_instance->m_arrays[array->GetID()] = Unique<VertexArray>(array);
}
Shared<GraphicsBuffer> BufferManager::GetGraphicsBuffer(uint id)
{
    return s_instance->m_buffers[id];
}
Shared<VertexArray> BufferManager::GetVertexArray(uint id)
{
    return s_instance->m_arrays[id];
}

}