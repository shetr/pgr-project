#include "TextureGen.hpp"

#include <core/manage/TextureManager.hpp>
#include <app/generate/Noise.hpp>

namespace sadekpet {

void TextureGen::Perlin3DSphere(const String& name, const PartialLerp<glm::vec3>& colors, uint32_t seed, float frequency, 
        int octaves, float lacunarity, float persistence)
{
    int width = 1024;
    int height = 1024;
    Vector<uint8_t> data(3*width*height);
    FractalPerlin3D perlin(seed, octaves, lacunarity, persistence);
    for(int h = 0; h < height; h++) {
        float tRatio = ((float)h) / (height-1);
        float theta = M_PI * tRatio;
        float sinTheta = glm::sin(theta);
        float mCosTheta = -glm::cos(theta);
        for(int w = 0; w < width; w++) {
            float pRatio = ((float)w) / (width-1);
            float phi =  2 * M_PI * pRatio;
            float sinPhi = glm::sin(phi);
            float cosPhi = glm::cos(phi);
            glm::vec3 pos = glm::vec3(sinTheta * cosPhi + 1, mCosTheta + 1, sinTheta * sinPhi + 1);
            float t = 0.5f*perlin.Value(pos, frequency)+0.5f;
            glm::vec3 col = colors.Value(t);
            uint8_t value = (uint8_t)(255 * t);
            int i = 3*(w + h * width);
            data[i+0] = (uint8_t)(255 * col.r);
            data[i+1] = (uint8_t)(255 * col.g);
            data[i+2] = (uint8_t)(255 * col.b);
        }
    }
    TextureManager::SaveTexture2DRGB(name, width, height, data.data());
}

void TextureGen::Perlin1DSphere(const String& name, const PartialLerp<glm::vec3>& colors, uint32_t seed, float frequency, 
        int octaves, float lacunarity, float persistence)
{
    int width = 1024;
    int height = 1024;
    Vector<uint8_t> data(3*width*height);
    FractalPerlin2D perlin(seed, octaves, lacunarity, persistence);
    for(int h = 0; h < height; h++) {
        float tRatio = ((float)h) / (height-1);
        float theta = M_PI * tRatio;
        float sinTheta = glm::sin(theta);
        float mCosTheta = -glm::cos(theta);
        glm::vec2 pos = glm::vec2(mCosTheta+1, sinTheta+1);
        float t = 0.5f*perlin.Value(pos, frequency)+0.5f;
        for(int w = 0; w < width; w++) {
            glm::vec3 col = colors.Value(t);
            uint8_t value = (uint8_t)(255 * t);
            int i = 3*(w + h * width);
            data[i+0] = (uint8_t)(255 * col.r);
            data[i+1] = (uint8_t)(255 * col.g);
            data[i+2] = (uint8_t)(255 * col.b);
        }
    }
    TextureManager::SaveTexture2DRGB(name, width, height, data.data());
}

}