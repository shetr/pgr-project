/**
 * @file BloomEffect.hpp
 * @author sadekpet (sadekpet@fel.cvut.cz)
 * @brief 
 * @date 2020-06-28
 */

#ifndef PGR_BLOOM_EFFECT_HPP
#define PGR_BLOOM_EFFECT_HPP

#include <core/render/PostProcessingEffect.hpp>
#include <core/render/Uniforms.hpp>
#include <core/render/Texture.hpp>
#include <core/render/Framebuffer.hpp>

namespace sadekpet {

class BloomEffect : public PostProcessingEffect
{
private:
    Uniform<int>* m_textureSampler;
    Uniform<bool>* m_horizontal;
    UniformArray<float>* m_weights;
    Unique<Framebuffer> pingpongFramebuffers[2];
    Shared<Texture2D> pingpongTextures[2];
    Unique<PostProcessingEffect> m_blur;
public:
    BloomEffect(int width, int height);
    void Run(Shared<Texture2D>& tex1, Shared<Texture2D>& tex2) override;
    void Resize(int width, int height) override;
};

}

#endif // PGR_BLOOM_EFFECT_HPP