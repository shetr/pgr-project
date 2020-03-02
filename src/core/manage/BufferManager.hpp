/**
 * @file BufferManger.hpp
 * @author sadekpet
 * @brief 
 * 
 */

#ifndef PGR_BUFFER_MANAGER_HPP
#define PGR_BUFFER_MANAGER_HPP

#include <core/render/Buffer.hpp>
#include <core/render/VertexArray.hpp>

namespace sadekpet {

class BufferManager
{
private:
    static BufferManager* s_instance;
    UnordMap<uint, Shared<GraphicsBuffer>> m_buffers;
    UnordMap<uint, Shared<VertexArray>> m_arrays;
public:
    static BufferManager* Init();
    ~BufferManager() { s_instance = nullptr; }

    static void AddGraphicsBuffer(GraphicsBuffer* buffer);
    static void AddVertexArray(VertexArray* array);

    static Shared<GraphicsBuffer> GetGraphicsBuffer(uint id);
    static Shared<VertexArray> GetVertexArray(uint id);
private:
    BufferManager() {}
};

}

#endif // PGR_BUFFER_MANAGER_HPP