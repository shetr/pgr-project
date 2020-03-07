/**
 * @file Material.hpp
 * @author sadekpet 
 * @brief 
 * 
 */

#ifndef PGR_MATERIAL_HPP
#define PGR_MATERIAL_HPP

#include "Primitives.hpp"
#include "Uniforms.hpp"
#include "Texture.hpp"

namespace sadekpet {

class Material
{
public:
    virtual TypeIndex GetType() const = 0;
    virtual const Shared<Primitives>& GetPrimitives() = 0;
    virtual Uniforms& GetUniforms() = 0;
    virtual TextureUnits& GetTextureUnits() = 0;
};

}

#endif // PGR_MATERIAL_HPP