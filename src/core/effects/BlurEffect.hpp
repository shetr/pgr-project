/**
 * @file BlurEffect.hpp
 * @author sadekpet (sadekpet@fel.cvut.cz)
 * @brief 
 * @date 2020-06-28
 */

#ifndef PGR_BLUR_EFFECT_HPP
#define PGR_BLUR_EFFECT_HPP

#include <core/render/PostProcessingEffect.hpp>
#include <core/render/Uniforms.hpp>
#include <core/render/Texture.hpp>
#include <core/render/Framebuffer.hpp>

namespace sadekpet {

class BlurEffect : public PostProcessingEffect
{
private:
    Uniform<int>* m_texture1Sampler;
    Uniform<int>* m_texture2Sampler;
public:
    BlurEffect();
    void Run(Shared<Texture2D>& tex1, Shared<Texture2D>& tex2) override;
};

}

#endif // PGR_BLUR_EFFECT_HPP