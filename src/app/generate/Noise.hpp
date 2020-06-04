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

/**
 * @brief Nadřázená třída pro generátor šumu.
 */
class Noise
{
private:
    Vector<uint32_t> m_hash;
public:
    Noise(uint32_t seed, uint32_t hashSize);
protected:
    uint32_t Hash(uint32_t i) const { return m_hash[i]; }
    uint32_t HashMask() const { return m_hash.size() - 1; }
    uint32_t HashSize() const { return m_hash.size(); }
    float Smooth(float t);
};

/**
 * @brief Jednorozměrný Perlin generátor šumu.
 */
class Perlin1D : public Noise
{
private:
    static float s_gradients[2];
    static uint32_t s_gradMask;
public:
    Perlin1D(uint32_t seed) : Noise(seed, 256) {}
    float Value(float pos, float freq);
};

/**
 * @brief Dvourozměrný Perlin generátor šumu.
 */
class Perlin2D: public Noise
{
private:
    static glm::vec2 s_gradients[8];
    static uint32_t s_gradMask;
public:
    Perlin2D(uint32_t seed) : Noise(seed, 256) {}
    float Value(glm::vec2 pos, float freq);
};

/**
 * @brief Třírozměrný Perlin generátor šumu.
 */
class Perlin3D: public Noise
{
private:
    static glm::vec3 s_gradients[16];
    static uint32_t s_gradMask;
public:
    Perlin3D(uint32_t seed) : Noise(seed, 256) {}
    float Value(glm::vec3 pos, float freq);
};

/**
 * @brief Fraktální generátor šumu - kombinace několika šumů s různou frekvencí a dašími parametry.
 * 
 * @tparam PositionType Typ vektrou
 * @tparam NoiseType Typ použitého šumu.
 */
template<typename PositionType, typename NoiseType>
class FractalNoise
{
private:
    NoiseType noise;
    int m_octaves;
    float m_lacunarity;
    float m_persistence;
public:
    FractalNoise(uint32_t seed, int octaves = 1, float lacunarity = 2, float persistence = 0.5)
        : noise(seed), m_octaves(octaves), m_lacunarity(lacunarity), m_persistence(persistence)
    {}
    float Value(PositionType pos, float freq)
    {
        float res = noise.Value(pos, freq);
        float ampl = 1;
        float range = 1;
        for(int o = 1; o < m_octaves; o++) {
            freq *= m_lacunarity;
            ampl *= m_persistence;
            range += ampl;
            res += noise.Value(pos, freq) * ampl;
        }
        return res / range;
    }
};

using FractalPerlin1D = FractalNoise<float, Perlin1D>;
using FractalPerlin2D = FractalNoise<glm::vec2, Perlin2D>;
using FractalPerlin3D = FractalNoise<glm::vec3, Perlin3D>;

}

#endif // PGR_NOISE_HPP