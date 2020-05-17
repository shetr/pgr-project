/**
 * @file TextureGen.hpp
 * @author sadekpet
 * @brief 
 * @date 2020-05-17
 * 
 */

#ifndef PGR_TEXTURE_GEN_HPP
#define PGR_TEXTURE_GEN_HPP

#include <core/types.hpp>
#include <core/math/PartialLerp.hpp>

namespace sadekpet {

class TextureGen
{
public:
    static void Perlin3DSphere(const String& name, const PartialLerp<glm::vec3>& colors, uint32_t seed, float frequency = 1, 
        int octaves = 1, float lacunarity = 2, float persistence = 0.5);
    
    static void Perlin1DSphere(const String& name, const PartialLerp<glm::vec3>& colors, uint32_t seed, float frequency = 1, 
        int octaves = 1, float lacunarity = 2, float persistence = 0.5);
};

}

#endif // PGR_TEXTURE_GEN_HPP