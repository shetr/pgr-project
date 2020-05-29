#include "ShaderContexts.hpp"

#include <core/manage/PrimitivesManager.hpp>
#include <core/manage/TextureManager.hpp>
#include <core/render/OpenGL.hpp>

#include "GlobalSceneState.hpp"

namespace sadekpet {

Object3DUniforms::Object3DUniforms(const Material& material)
{ 
    m_textureSampler = new Uniform<int>("textureSampler", 0);
    m_material = new MaterialUniform("material", material);
    dirLight = new LightUniform("dirLight");
    pointLight = new LightUniform("pointLight");
    spotLight = new LightUniform("spotLight");
    AddUniform(m_textureSampler);
    AddUniform(m_material);
    AddUniform(dirLight);
    AddUniform(pointLight);
    AddUniform(spotLight);
}

Object3DShaderContext::Object3DShaderContext(const String& mesh, const String& texture, const Material& material)
    : m_textureUnits(Vector<Shared<Texture>>({TextureManager::GetTexture(texture)})), m_uniforms(material)
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
    Object3DUniforms& uniforms = m_shaderContext->GetObject3DUniforms();
    uniforms.dirLight->UpdateLight(GlobalSceneState::dirLight);
    uniforms.pointLight->UpdateLight(GlobalSceneState::pointLight);
    uniforms.spotLight->UpdateLight(GlobalSceneState::spotLight);
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


Line3DUniforms::Line3DUniforms(glm::vec3 color)
{
    m_color = new Uniform<glm::vec3>("color", color);
    AddUniform(m_color);
}

Line3DShaderContext::Line3DShaderContext(Line3D* lines, float width, glm::vec3 color)
    : m_width(width), m_textureUnits(Vector<Shared<Texture>>({})), m_uniforms(color)
{
    m_lines = Shared<Primitives>(lines);
}
TypeIndex Line3DShaderContext::GetType() const
{
    return TypeIndex(typeid(Line3DShaderContext));
}
const Shared<Primitives>& Line3DShaderContext::GetPrimitives()
{
    return m_lines;
}
Uniforms& Line3DShaderContext::GetUniforms()
{
    return m_uniforms;
}
TextureUnits& Line3DShaderContext::GetTextureUnits()
{
    return m_textureUnits;
}

Line3DShaderContextUpdater::Line3DShaderContextUpdater(Line3DShaderContext* shaderContext)
    : m_shaderContext(shaderContext)
{

}
void Line3DShaderContextUpdater::Update()
{
    //GL(LineWidth(m_shaderContext->GetWidth()));
}

}