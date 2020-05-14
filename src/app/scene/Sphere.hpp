/**
 * @file Sphere.hpp
 * @author sadekpet
 * @brief 
 * @date 2020-03-10
 * 
 */

#ifndef PGR_SHPERE_HPP
#define PGR_SHPERE_HPP

#include <core/scene/Node.hpp>
#include <core/render/ShaderContext.hpp>

namespace sadekpet {

class SphereShaderContext : public ShaderContext {
private:
    Shared<Primitives> m_mesh;
    Uniforms m_uniforms;
    TextureUnits m_textureUnits = TextureUnits({});
public:
    SphereShaderContext();
    TypeIndex GetType() const override;
    const Shared<Primitives>& GetPrimitives() override;
    Uniforms& GetUniforms() override;
    TextureUnits& GetTextureUnits() override;
};

class SphereNode : public VisibleNode {
private:
    SphereShaderContext m_shaderContext;
public:
    SphereNode() { m_shaderContext.GetUniforms().SetOwner(this); }
    ShaderContext& GetShaderContext() override { return m_shaderContext; }
};

}

#endif // PGR_SHPERE_HPP