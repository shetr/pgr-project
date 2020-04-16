/**
 * @file Noise.hpp
 * @author sadekpet ()
 * @date 2020-04-15
 * @brief 
 * 
 */

#ifndef PGR_NOISE_HPP
#define PGR_NOISE_HPP

#include "Random.hpp"
#include <glm/glm.hpp>

namespace sadekpet {

class Noise
{
private:
    Vector<uint32_t> m_hash;
public:
    Noise(uint32_t seed, uint32_t hashSize);
protected:
    uint32_t Hash(uint32_t i) const { return m_hash[i]; }
    uint32_t HashMask() const { return m_hash.size() - 1; }
    float Smooth(float t);
};

class Perlin1D : public Noise
{
private:
    static float s_gradients[2];
    static uint32_t s_gradMask;
public:
    Perlin1D(uint32_t seed, uint32_t hashSize = 128) : Noise(seed, hashSize) {}
    float Value(float pos, float freq);
};

class Perlin2D: public Noise
{
private:
    static glm::vec2 s_gradients[8];
    static uint32_t s_gradMask;
public:
    Perlin2D(uint32_t seed, uint32_t hashSize = 256) : Noise(seed, hashSize) {}
    float Value(glm::vec2 pos, float freq);
};

}

#endif // PGR_NOISE_HPP