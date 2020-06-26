/**
 * @file Renderbuffer.hpp
 * @author sadekpet (sadekpet@fel.cvut.cz)
 * @brief 
 * @date 2020-06-26
 */

#ifndef PGR_RENDERBUFFER_HPP
#define PGR_RENDERBUFFER_HPP

#include <core/types.hpp>

namespace sadekpet {

class Renderbuffer
{
private:
    uint m_id;
public:
    Renderbuffer();
    ~Renderbuffer();
    void Bind();
    static void UnBind();
    uint GetID() const { return m_id; }
    void StorageDephtStencil(int width, int height);
};

}

#endif // PGR_RENDERBUFFER_HPP