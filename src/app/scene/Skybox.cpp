#include "Skybox.hpp"

#include <core/manage/PrimitivesManager.hpp>
#include <core/manage/TextureManager.hpp>

namespace sadekpet {

SkyboxUniforms::SkyboxUniforms() 
{ 
    m_textureSampler = new Uniform<int>("textureSampler", 0);
    AddUniform(m_textureSampler);
}

SkyboxShaderContext::SkyboxShaderContext(const String& texture)
    : m_textureUnits(Vector<Shared<Texture>>({TextureManager::GetTexture(texture)}))
{
    m_mesh = PrimitivesManager::GetPrimitives("cube");
}

TypeIndex SkyboxShaderContext::GetType() const
{
    return TypeIndex(typeid(SkyboxShaderContext));
}
const Shared<Primitives>& SkyboxShaderContext::GetPrimitives()
{
    return m_mesh;
}
Uniforms& SkyboxShaderContext::GetUniforms()
{
    return m_uniforms;
}
TextureUnits& SkyboxShaderContext::GetTextureUnits()
{
    return m_textureUnits;
}

}