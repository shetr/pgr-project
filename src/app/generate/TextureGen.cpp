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

void TextureGen::Perlin3DSphereAlpha(const String& name, const PartialLerp<glm::vec4>& colors, uint32_t seed, float frequency, 
        int octaves, float lacunarity, float persistence)
{
    int width = 1024;
    int height = 1024;
    Vector<uint8_t> data(4*width*height);
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
            glm::vec4 col = colors.Value(t);
            uint8_t value = (uint8_t)(255 * t);
            int i = 4*(w + h * width);
            data[i+0] = (uint8_t)(255 * col.r);
            data[i+1] = (uint8_t)(255 * col.g);
            data[i+2] = (uint8_t)(255 * col.b);
            data[i+3] = (uint8_t)(255 * col.a);
        }
    }
    TextureManager::SaveTexture2DRGBA(name, width, height, data.data());
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


void TextureGen::SmokeAnimation(const String& name, glm::ivec2 sizes, const PartialLerp<glm::vec4>& colors, uint32_t seed, float frequency, 
        int octaves, float lacunarity, float persistence)
{
    int width = 1024;
    int height = 1024;
    int wStep = width / sizes.x;
    int hStep = height / sizes.y;
    Vector<uint8_t> data(4*width*height);
    FractalPerlin2D perlin(seed, octaves, lacunarity, persistence);
    float time = 0;
    float tmax = sizes.x * sizes.y - 1;
    for(int hStart = 0; hStart < height; hStart += hStep) {
        for(int wStart = 0; wStart < width; wStart += wStep, time+=1.0f) {
            for(int h = 0; h < hStep; h++) {
                float timeRatio = time/tmax;
                float tRatio = ((float)h) / (hStep-1);
                for(int w = 0; w < wStep; w++) {
                    float pRatio = ((float)w) / (wStep-1);
                    glm::vec2 pos = glm::vec2(pRatio, tRatio);
                    float x = pRatio - 0.5f;
                    float y = tRatio - 0.5f;
                    float alpha = glm::clamp(1.0f / (1.0f + 20.0f*(x*x + y*y)) - 1.0f/6.0f, 0.0f, 1.0f);
                    float t = 0.5f*perlin.Value(pos, frequency)+0.5f;
                    glm::vec4 col = colors.Value(t);
                    int i = 4*(wStart + w + (hStart + h) * width);
                    data[i+0] = (uint8_t)(255 * col.r);
                    data[i+1] = (uint8_t)(255 * col.g);
                    data[i+2] = (uint8_t)(255 * col.b);
                    data[i+3] = (uint8_t)(255 * col.a * (1.0f - timeRatio) * alpha);
                }
            }
        }
    }
    TextureManager::SaveTexture2DRGBA(name, width, height, data.data());
}

}