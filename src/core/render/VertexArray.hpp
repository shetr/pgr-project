#ifndef PGR_VERTEX_ARRAY_HPP
#define PGR_VERTEX_ARRAY_HPP

#include "Buffer.hpp"


namespace sadekpet
{

/**
 * @brief Abstrakce opengl vertex array.
 */
class VertexArray
{
protected:
    uint m_id;
    uint m_elementCount = 0;
    uint m_size = 0;
    Vector<VertexLayout> m_layouts;
public:
    VertexArray();
    ~VertexArray();

    void Bind() const;
    static void UnBind();

    int GetSize() const { return m_size; }
    uint GetID() const { return m_id; }

    void SetIndexBuffer(const Shared<IndexBuffer>& indexBuffer);
    
    template<typename Vertex>
    void AddVertexBuffer(const Shared<VertexBuffer<Vertex>>& vertexBuffer){
        Bind();
        vertexBuffer->Bind();
        VertexLayout layout = vertexBuffer->GetLayout();
        m_layouts.push_back(layout);
        for(const VertexElement& element: layout.Elements()) {
            EnableVertexAttribArray(m_elementCount);
            VertexAttribPointer(
                m_elementCount,
                element.Count(),
                static_cast<uint>(element.GetType()),
                element.IsNormalized(),
                layout.GetStride(),
                (const void*)(intptr_t)element.GetOffset()
            );
            m_elementCount++;
        }
    }

    Vector<VertexLayout>& GetLayouts() { return m_layouts; }
    void SetDivisors();
private:
    void EnableVertexAttribArray(uint i);
    void VertexAttribPointer(uint i, int count, uint type, bool normalized, uint stride, const void* offset);
};

}

#endif // PGR_VERTEX_ARRAY_HPP