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

namespace sadekpet {

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
};

}

#endif // PGR_FRAMEBUFFER_HPP