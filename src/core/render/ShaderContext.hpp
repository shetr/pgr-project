/**
 * @file ShaderContext.hpp
 * @author sadekpet 
 * @brief 
 * 
 */

#ifndef PGR_SHADER_CONTEXT_HPP
#define PGR_SHADER_CONTEXT_HPP

#include "Primitives.hpp"
#include "Uniforms.hpp"
#include "Texture.hpp"

namespace sadekpet {

/**
 * @brief Popisuje data potřebná při vykonání příslušného shaderu.
 */
class ShaderContext
{
public:
    virtual TypeIndex GetType() const = 0;
    virtual const Shared<Primitives>& GetPrimitives() = 0;
    virtual Uniforms& GetUniforms() = 0;
    virtual TextureUnits& GetTextureUnits() = 0;
    virtual void DrawFunction();
};

class InstancedShaderContext : public ShaderContext
{
public:
    virtual uint GetStartIndex() const { return 0; }
    virtual uint GetVertexCount() const = 0;
    virtual uint GetInstanceCount() const = 0;
    virtual void DrawFunction() override;
protected:
    virtual void BeforeDraw() = 0;
};

}

#endif // PGR_SHADER_CONTEXT_HPP