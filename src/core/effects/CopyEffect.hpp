/**
 * @file CopyEffect.hpp
 * @author sadekpet (sadekpet@fel.cvut.cz)
 * @brief 
 * @date 2020-06-27
 */

#ifndef PGR_COPY_EFFECT_HPP
#define PGR_COPY_EFFECT_HPP

#include <core/render/PostProcessingEffect.hpp>
#include <core/render/Uniforms.hpp>

namespace sadekpet {

class CopyEffect : public PostProcessingEffect
{
private:
    Uniform<int>* m_textureSampler;
public:
    CopyEffect();
    void Run(Shared<Texture2D>& frame) override;
};

}

#endif // PGR_COPY_EFFECT_HPP