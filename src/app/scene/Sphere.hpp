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

class SphereUniforms : public Uniforms
{
private:
    Uniform<int>* m_textureSampler;
public:
    SphereUniforms() { 
        m_textureSampler = new Uniform<int>("textureSampler", 0);
        AddUniform(m_textureSampler);
    }
};

class SphereShaderContext : public ShaderContext {
private:
    Shared<Primitives> m_mesh;
    SphereUniforms m_uniforms;
    TextureUnits m_textureUnits;
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
    SphereNode() { }
    ShaderContext& GetShaderContext() override { return m_shaderContext; }
};

}

#endif // PGR_SHPERE_HPP