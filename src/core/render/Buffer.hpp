/**
 * @file buffer.hpp
 * @author sadekpet 
 * @brief 
 * 
 */

#ifndef PGR_GRAPHICS_BUFFER_HPP
#define PGR_GRAPHICS_BUFFER_HPP

#include <core/types.hpp>

namespace sadekpet 
{

enum class GraphicsBufferTarget : uint32_t
{
    ARRAY = 0x8892,
    ATOMIC_COUNTER = 0x92C0,
    COPY_READ = 0x8F36,
    COPY_WRITE = 0x8F37,
    DISPATCH_INDIRECT = 0x90EE,
    DRAW_INDIRECT = 0x8F3F,
    ELEMENT_ARRAY = 0x8893,
    PARAMETER = 0x80EE,
    PIXEL_PACK = 0x88EB,
    PIXEL_UNPACK = 0x88EC,
    QUERY = 0x9192,
    SHADER_STORAGE = 0x90D2,
    TEXTURE = 0x8C2A,
    TRANSFORM_FEEDBACK = 0x8C8E,
    UNIFORM = 0x8A11
};

enum class GraphicsBufferUsage : uint32_t
{
    STREAM_DRAW = 0x88E0,
    STREAM_READ = 0x88E1,
    STREAM_COPY = 0x88E2,
    STATIC_DRAW = 0x88E4,
    STATIC_READ = 0x88E5,
    STATIC_COPY = 0x88E6,
    DYNAMIC_DRAW = 0x88E8,
    DYNAMIC_READ = 0x88E9,
    DYNAMIC_COPY = 0x88EA
};

class GraphicsBuffer
{
protected:
    uint32_t m_id;
    int m_size;
    const void* m_data;
    GraphicsBufferUsage m_usage;
    GraphicsBufferTarget m_target;
public:
    virtual ~GraphicsBuffer();

    GraphicsBufferTarget GetTarget() { return m_target; }

    void Bind();
    void UnBind();

    int GetSize() const { return m_size; }
    uint32_t GetID() const { return m_id; }
protected:
    void Init();
    GraphicsBuffer(int size, const void* data, GraphicsBufferTarget target);
    GraphicsBuffer(int size, const void* data, GraphicsBufferTarget target, GraphicsBufferUsage usage);
};

enum class VertexType : uint32_t
{
    INT8 = 0x1400,
    UINT8 = 0x1401,
    INT16 = 0x1402,
    UINT16 = 0x1403,
    INT32 = 0x1404,
    UINT32 = 0x1405,
    FLOAT16 = 0x140B,
    FLOAT32 = 0x1406,
    FLOAT64 = 0x140A,
    FIXED = 0x140C
};

enum class VertexElementCount : int32_t
{
    _1 = 1,
    _2 = 2,
    _3 = 3,
    _4 = 4
};

class VertexElement
{
private:
    VertexType m_type;
    VertexElementCount m_count;
    bool m_normalized;
    uint m_offset = 0;
public:
    VertexElement(VertexType type, VertexElementCount count)
        : m_type(type), m_count(count), m_normalized(false)
    {}
    VertexElement(VertexType type, VertexElementCount count, bool normalized)
        : m_type(type), m_count(count), m_normalized(normalized)
    {}

    inline VertexType GetType() const { return m_type; }
    inline int Count() const { return static_cast<int>(m_count); }
    inline bool IsNormalized() const { return m_normalized; }
    inline int ByteSize() const { return Count() * TypeSize(m_type); }
    inline void SetOffset(uint offset) { m_offset = offset; }
    inline uint GetOffset() const { return m_offset; }

    static int TypeSize(VertexType type);
};

class VertexLayout
{
private:
    Vector<VertexElement> m_elements;
    uint m_stride = 0;
public:
    VertexLayout() : m_elements() {}
    VertexLayout(const Vector<VertexElement>& elements) : m_elements(elements) {
        for(VertexElement& element: m_elements){
            element.SetOffset(m_stride);
            m_stride += element.ByteSize();
        }
    }

    inline void AddElement(const VertexElement& element) { 
        m_elements.push_back(element);
        m_elements.back().SetOffset(m_stride);
        m_stride += element.ByteSize();
    }
    inline int ElementsCount() const { return m_elements.size(); }
    inline const Vector<VertexElement>& Elements() const { return m_elements; }
    int ByteSize() const;
    uint GetStride() const { return m_stride; }
};

template<typename Vertex>
class VertexBuffer : public GraphicsBuffer
{
protected:
    VertexBuffer(int size, const Vertex* vertices)
    : GraphicsBuffer(size, vertices, GraphicsBufferTarget::ARRAY) {}
    VertexBuffer(int size, const Vertex* vertices, GraphicsBufferUsage usage)
    : GraphicsBuffer(size, vertices, GraphicsBufferTarget::ARRAY, usage) {}
public:
    static VertexBuffer* Create(int size, const Vertex* vertices) {
        VertexBuffer* buffer = new VertexBuffer(size, vertices);
        buffer->Bind();
        buffer->Init();
        return buffer;
    }
    static VertexBuffer* Create(int size, const Vertex* vertices, GraphicsBufferUsage usage) {
        VertexBuffer* buffer = new VertexBuffer(size, vertices, usage);
        buffer->Bind();
        buffer->Init();
        return buffer;
    }

    inline const VertexLayout& GetLayout() const { 
        return Vertex::GetLayout();
    }
};

class IndexBuffer : public GraphicsBuffer
{
protected:
    IndexBuffer(int size, const int* indices)
    : GraphicsBuffer(size, indices, GraphicsBufferTarget::ELEMENT_ARRAY) {}
    IndexBuffer(int size, const int* indices, GraphicsBufferUsage usage)
    : GraphicsBuffer(size, indices, GraphicsBufferTarget::ELEMENT_ARRAY, usage) {}
public:
    static IndexBuffer* Create(int size, const int* indices);
    static IndexBuffer* Create(int size, const int* indices, GraphicsBufferUsage usage);
};

}

#endif // PGR_GRAPHICS_BUFFER_HPP