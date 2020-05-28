#include "Testing.hpp"

#include <iostream>

#include <core/math/Math.hpp>
#include <core/math/PartialLerp.hpp>
#include <core/manage/TextureManager.hpp>
#include <app/generate/Noise.hpp>
#include <app/generate/TextureGen.hpp>

namespace sadekpet {

void g_TestGenNoiseImage()
{
    int width = 512;
    int height = 512;
    Vector<uint8_t> data(3*width*height);
    FractalPerlin2D perlin(21, 2);
    glm::vec3 col1 = glm::vec3(0, 0, 1);
    glm::vec3 col2 = glm::vec3(0, 1, 0);
    for(int w = 0; w < width; w++) {
        for(int h = 0; h < height; h++) {
            glm::vec2 pos = glm::vec2(w, h) / 10.0f;
            float t = 0.5f*perlin.Value(pos, 0.05f)+0.5f;
            glm::vec3 col = Math::Lerp(col1, col2, t);
            uint8_t value = (uint8_t)(255 * t);
            int i = 3*(w + h * width);
            data[i+0] = (uint8_t)(255 * col.r);
            data[i+1] = (uint8_t)(255 * col.g);
            data[i+2] = (uint8_t)(255 * col.b);
        }
    }
    TextureManager::SaveTexture2DRGB("generated/perlinTest.png", width, height, data.data());
}

void g_TestGenSphereNoise()
{
    int width = 1024;
    int height = 1024;
    Vector<uint8_t> data(3*width*height);
    FractalPerlin3D perlin(3, 2, 4);
    PartialLerp<glm::vec3> partLerp({
        {0, glm::vec3(0.6, 0, 0)},
        {0.6, glm::vec3(0.7, 0.7, 0)},
        {1, glm::vec3(1, 1, 1)}
    });
    /*glm::vec3 col1 = glm::vec3(0, 0, 0);
    glm::vec3 col2 = glm::vec3(1, 1, 1);*/
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
            //glm::vec3 pos = glm::vec3(Math::Lerp(-0.5, 0.5, pRatio), Math::Lerp(-0.5, 0.5, tRatio), 1);
            float t = 0.5f*perlin.Value(pos, 3.0f)+0.5f;
            //glm::vec3 col = Math::Lerp(col1, col2, t);
            glm::vec3 col = partLerp.Value(t);
            uint8_t value = (uint8_t)(255 * t);
            int i = 3*(w + h * width);
            data[i+0] = (uint8_t)(255 * col.r);
            data[i+1] = (uint8_t)(255 * col.g);
            data[i+2] = (uint8_t)(255 * col.b);
        }
    }
    TextureManager::SaveTexture2DRGB("generated/perlinSun.png", width, height, data.data());
}


void g_TestGenSpaceNoise()
{
    Array<String, 6> names = {
        "generated/space_px.jpg",
        "generated/space_nx.jpg",
        "generated/space_py.jpg",
        "generated/space_ny.jpg",
        "generated/space_pz.jpg",
        "generated/space_nz.jpg",
    };
    Array<glm::vec3,6> posVecs = {
        glm::vec3( 1,  1,  0),
        glm::vec3( 1,  1,  1),
        glm::vec3( 0,  0,  1),
        glm::vec3( 0,  1,  0),
        glm::vec3( 0,  1,  1),
        glm::vec3( 0,  1,  0)
    };
    Array<glm::vec3,6> dirVecs1 = {
        glm::vec3(-1,  0,  0),
        glm::vec3( 0,  0, -1),
        glm::vec3( 1,  0,  0),
        glm::vec3( 1,  0,  0),
        glm::vec3( 1,  0,  0),
        glm::vec3( 0,  0,  1)
    };
    Array<glm::vec3,6> dirVecs2 = {
        glm::vec3( 0, -1,  0),
        glm::vec3( 0, -1,  0),
        glm::vec3( 0,  0, -1),
        glm::vec3( 0,  0,  1),
        glm::vec3( 0, -1,  0),
        glm::vec3( 0, -1,  0)
    };
    int width = 1024;
    int height = 1024;
    FractalPerlin3D perlin(15, 2);
    float threashold = 0.7;
    for(int i = 0; i < 6; i++) {
        Vector<uint8_t> data(3*width*height);
        glm::vec3 pos = posVecs[i];
        glm::vec3 dir1 = dirVecs1[i];
        glm::vec3 dir2 = dirVecs2[i];
        for(int w = 0; w < width; w++) {
            for(int h = 0; h < height; h++) {
                float a1 = w / ((float)width - 1);
                float a2 = h / ((float)height - 1);
                glm::vec3 v = glm::normalize(pos + a1*dir1 + a2*dir2 - glm::vec3(0.5,0.5,0.5));
                float t = 0.5f*perlin.Value(0.5f*v+0.5f, 250)+0.5f;
                if(t < threashold) {
                    t = 0;
                } else {
                    t = 0.75f * (t - threashold) / (1 - threashold);
                }
                uint8_t value = (uint8_t)(255 * t);
                int i = 3*(w + h * width);
                data[i+0] = value;
                data[i+1] = value;
                data[i+2] = value;
            }
        }
        TextureManager::SaveTexture2DRGB(names[i], width, height, data.data());
    }
}

void g_GenTextures()
{
    PartialLerp<glm::vec3> colorsPlanet1({
        {0, glm::vec3(0.54, 0.54, 0.59)},
        {0.5, glm::vec3(0.47, 0.46, 0.47)},
        {1, glm::vec3(0.65, 0.64, 0.63)}
    });
    TextureGen::Perlin3DSphere("generated/planet1.png", colorsPlanet1, 13, 8, 2, 4);
/*
    PartialLerp<glm::vec3> colorsPlanet2({
        {0, glm::vec3(0.64, 0.59, 0.07)},
        {0.5, glm::vec3(0.42, 0.31, 0.04)},
        {1, glm::vec3(0.58, 0.27, 0.12)}
    });
    TextureGen::Perlin3DSphere("generated/planet2.png", colorsPlanet2, 26, 1, 3);
*/
    /* 
    PartialLerp<glm::vec3> colorsPlanet3({
        {0, glm::vec3(0, 0, 0.5)},
        {0.5, glm::vec3(0, 0.33, 1)},
        {0.51, glm::vec3(0, 0.43, 0)},
        {0.6, glm::vec3(0.2, 0.5, 0)},
        {0.8, glm::vec3(0.64, 0.49, 0.11)},
        {1, glm::vec3(0.58, 0.36, 0.11)}
    });
    TextureGen::Perlin3DSphere("generated/planet3.png", colorsPlanet1, 4, 1.5, 3);*/
/*
    PartialLerp<glm::vec3> colorsPlanet5({
        {0, glm::vec3(0.82, 0.82, 0.85)},
        {0.5, glm::vec3(0.59, 0.37, 0.3)},
        {1, glm::vec3(0.8, 0.74, 0.64)}
    });
    TextureGen::Perlin1DSphere("generated/planet5.png", colorsPlanet5, 12, 2, 3);
*/
/*
    PartialLerp<glm::vec3> colorsPlanet6({
        {0, glm::vec3(0.4, 0.5, 0.63)},
        {0.5, glm::vec3(0.4, 0.5, 0.69)},
        {1, glm::vec3(0.66, 0.75, 0.89)}
    });
    TextureGen::Perlin1DSphere("generated/planet6.png", colorsPlanet6, 213, 1, 3);
*/
}

}