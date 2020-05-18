#include "ShaderContexts.hpp"

#include <core/manage/PrimitivesManager.hpp>
#include <core/manage/TextureManager.hpp>

namespace sadekpet {

Object3DUniforms::Object3DUniforms() 
{ 
    m_textureSampler = new Uniform<int>("textureSampler", 0);
    AddUniform(m_textureSampler);
}

Object3DShaderContext::Object3DShaderContext(const String& mesh, const String& texture)
    : m_textureUnits(Vector<Shared<Texture>>({TextureManager::GetTexture(texture)}))
{
    m_mesh = PrimitivesManager::GetPrimitives(mesh);
}

TypeIndex Object3DShaderContext::GetType() const
{
    return TypeIndex(typeid(Object3DShaderContext));
}
const Shared<Primitives>& Object3DShaderContext::GetPrimitives()
{
    return m_mesh;
}
Uniforms& Object3DShaderContext::GetUniforms()
{
    return m_uniforms;
}
TextureUnits& Object3DShaderContext::GetTextureUnits()
{
    return m_textureUnits;
}

Object3DShaderContextUpdater::Object3DShaderContextUpdater(Object3DShaderContext* shaderContext)
    : m_shaderContext(shaderContext)
{}

void Object3DShaderContextUpdater::Update()
{

}


Basic3DUniforms::Basic3DUniforms() 
{ 
    m_textureSampler = new Uniform<int>("textureSampler", 0);
    AddUniform(m_textureSampler);
}

Basic3DShaderContext::Basic3DShaderContext(const String& mesh, const String& texture)
    : m_textureUnits(Vector<Shared<Texture>>({TextureManager::GetTexture(texture)}))
{
    m_mesh = PrimitivesManager::GetPrimitives(mesh);
}

TypeIndex Basic3DShaderContext::GetType() const
{
    return TypeIndex(typeid(Basic3DShaderContext));
}
const Shared<Primitives>& Basic3DShaderContext::GetPrimitives()
{
    return m_mesh;
}
Uniforms& Basic3DShaderContext::GetUniforms()
{
    return m_uniforms;
}
TextureUnits& Basic3DShaderContext::GetTextureUnits()
{
    return m_textureUnits;
}

}