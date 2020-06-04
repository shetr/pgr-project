/**
 * @file Skybox.hpp
 * @author sadekpet (sadekpet@fel.cvut.cz)
 * @brief 
 * @date 2020-05-27
 */

#ifndef PGR_SKYBOX_HPP
#define PGR_SKYBOX_HPP

#include <core/render/ShaderContext.hpp>
#include <core/scene/Node.hpp>

namespace sadekpet {

/**
 * @brief Uniforms pro skybox shader.
 */
class SkyboxUniforms : public Uniforms
{
private:
    Uniform<int>* m_textureSampler;
public:
    SkyboxUniforms();
};

/**
 * @brief ShaderContext pro skybox shader.
 */
class SkyboxShaderContext : public ShaderContext {
private:
    Shared<Primitives> m_mesh;
    SkyboxUniforms m_uniforms;
    TextureUnits m_textureUnits;
public:
    SkyboxShaderContext(const String& texture);
    TypeIndex GetType() const override;
    const Shared<Primitives>& GetPrimitives() override;
    Uniforms& GetUniforms() override;
    TextureUnits& GetTextureUnits() override;
};

/**
 * @brief Node obsahující ShaderContext na vykreslení skyboxu.
 */
class Skybox : public VisibleNode
{
private:
    SkyboxShaderContext m_shaderContext;
public:
    Skybox(const String& texture) : m_shaderContext(texture) {}
    ShaderContext& GetShaderContext() override { return m_shaderContext; }
};

}

#endif // PGR_SKYBOX_HPP