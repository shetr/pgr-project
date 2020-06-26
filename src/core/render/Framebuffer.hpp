/**
 * @file Framebuffer.hpp
 * @author sadekpet (sadekpet@fel.cvut.cz)
 * @brief 
 * @date 2020-06-25
 */

#ifndef PGR_FRAMEBUFFER_HPP
#define PGR_FRAMEBUFFER_HPP

#include <core/types.hpp>

#include "Texture.hpp"
#include "Renderbuffer.hpp"

namespace sadekpet {

enum class FramebufferColor : uint
{
    _0  = 0x8CE0 ,
    _1  = 0x8CE1 ,
    _2  = 0x8CE2 ,
    _3  = 0x8CE3 ,
    _4  = 0x8CE4 ,
    _5  = 0x8CE5 ,
    _6  = 0x8CE6 ,
    _7  = 0x8CE7 ,
    _8  = 0x8CE8 ,
    _9  = 0x8CE9 ,
    _10 = 0x8CE10,
    _11 = 0x8CE11,
    _12 = 0x8CE12,
    _13 = 0x8CE13,
    _14 = 0x8CE14,
    _15 = 0x8CE15
};

class Framebuffer
{
private:
    uint32_t m_id;
public:
    Framebuffer();
    ~Framebuffer();

    void Bind() const;
    static void UnBind();

    bool IsComplete() const;

    void AttachTexture2D(const Shared<Texture2D>& texture, FramebufferColor attachment);
    void AttachRenderbufferDepthStencil(const Shared<Renderbuffer>& renderbuffer);
};

}

#endif // PGR_FRAMEBUFFER_HPP