#include "Noise.hpp"

#include <core/math/Math.hpp>

namespace sadekpet {

float Perlin1D::s_gradients[2] = {
    1, -1
};
glm::vec2 Perlin2D::s_gradients[8] = {
    glm::vec2( 1, 0),
    glm::vec2(-1, 0),
    glm::vec2( 0, 1),
    glm::vec2( 0,-1),
    glm::normalize(glm::vec2( 1, 1)),
    glm::normalize(glm::vec2(-1, 1)),
    glm::normalize(glm::vec2( 1,-1)),
    glm::normalize(glm::vec2(-1,-1)),
};
uint32_t Perlin1D::s_gradMask = 1;
uint32_t Perlin2D::s_gradMask = 7;

Noise::Noise(uint32_t seed, uint32_t hashSize)
    : m_hash(hashSize)
{
    LinCongRand gen(seed);
    for(uint32_t& h : m_hash) {
        h = gen.Next(HashMask());
    }
}

float Noise::Smooth(float t) 
{
    return t * t * t * (t * (t * 6.0f - 15.0f) + 10.0f);
}

float Perlin1D::Value(float pos, float freq)
{
    pos *= freq;
    int i = static_cast<int>(pos);
    float t0 = pos - i;
    float t1 = t0 - 1;
    uint32_t x0 = HashMask() & i;
    uint32_t x1 = x0 + 1;
    uint32_t h0 = Hash(x0);
    uint32_t h1 = Hash(x1);
    float g0 = s_gradients[h0 & s_gradMask];
    float g1 = s_gradients[h1 & s_gradMask];
    float v0 = g0 * t0;
    float v1 = g1 * t1;
    float t = Smooth(t0);
    return Math::Lerp(v0, v1, t) * 2;
}

float Perlin2D::Value(glm::vec2 pos, float freq)
{
    pos *= freq;
    int ix = static_cast<int>(pos.x);
    int iy = static_cast<int>(pos.y);
    float tx0 = pos.x - ix;
    float tx1 = tx0 - 1;
    float ty0 = pos.y - iy;
    float ty1 = ty0 - 1;
    uint32_t x0 = HashMask() & ix;
    uint32_t x1 = x0 + 1;
    uint32_t y0 = HashMask() & iy;
    uint32_t y1 = y0 + 1;

    uint32_t h0 = Hash(x0);
    uint32_t h1 = Hash(x1);
    glm::vec2 g00 = s_gradients[Hash(h0 + y0) & s_gradMask];
    glm::vec2 g10 = s_gradients[Hash(h1 + y0) & s_gradMask];
    glm::vec2 g01 = s_gradients[Hash(h0 + y1) & s_gradMask];
    glm::vec2 g11 = s_gradients[Hash(h1 + y1) & s_gradMask];
    float v00 = glm::dot(g00, glm::vec2(tx0, ty0));
    float v10 = glm::dot(g10, glm::vec2(tx1, ty0));
    float v01 = glm::dot(g01, glm::vec2(tx0, ty1));
    float v11 = glm::dot(g11, glm::vec2(tx1, ty1));

    float tx = Smooth(tx0);
    float ty = Smooth(ty0);
    return Math::Lerp(Math::Lerp(v00, v10, tx), Math::Lerp(v01, v11, tx), ty) * M_SQRT2;
}

}