/**
 * @file PostProcessingEffect.hpp
 * @author sadekpet (sadekpet@fel.cvut.cz)
 * @brief 
 * @date 2020-06-26
 * 
 */

#ifndef PGR_POST_PROCESSING_EFFECT_HPP
#define PGR_POST_PROCESSING_EFFECT_HPP

#include "ShaderContext.hpp"
#include "Texture.hpp"

namespace sadekpet {

#include "Primitives.hpp"

class PostProcessingEffect
{
private:
    static glm::vec2 s_QuadVertices[4];
    static glm::vec2 s_QuadUvs[4];
    static int s_QuadIndices[6];
protected:
    Shared<Mesh2D> m_windowQuad;
public:
    PostProcessingEffect();
    virtual void Run(Shared<Texture2D>& frame) {}
    virtual void Run(Shared<Texture2D>& tex1, Shared<Texture2D>& tex2) {}
    virtual void Resize(int width, int height) {}
};

}

#endif // PGR_POST_PROCESSING_EFFECT_HPP