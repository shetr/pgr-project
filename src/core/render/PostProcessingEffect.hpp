/**
 * @file PostProcessingEffect.hpp
 * @author sadekpet (sadekpet@fel.cvut.cz)
 * @brief 
 * @date 2020-06-26
 * 
 */

#ifndef PGR_POST_PROCESSING_EFFECT_HPP
#define PGR_POST_PROCESSING_EFFECT_HPP

#include "Texture.hpp"

namespace sadekpet {

class PostProcessingEffect
{
public:
    virtual void Run(const Shared<Texture2D>& frame);
};

}

#endif // PGR_POST_PROCESSING_EFFECT_HPP