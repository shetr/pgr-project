#include "ShaderContexts.hpp"

#include <core/manage/PrimitivesManager.hpp>
#include <core/manage/TextureManager.hpp>
#include <core/render/OpenGL.hpp>

#include "GlobalSceneState.hpp"

namespace sadekpet {

Object3DUniforms::Object3DUniforms(const Material& material)
{ 
    m_textureSampler = new Uniform<int>("textureSampler", 0);
    m_optTextureSampler = new Uniform<int>("optTextureSampler", 1);
    m_material = new MaterialUniform("material", material);
    dirLight = new LightUniform("dirLight");
    pointLight = new LightUniform("pointLight");
    spotLight = new LightUniform("spotLight");
    textureMat = new Uniform<glm::mat3>("textureMat", glm::mat3(1));
    fog = new Uniform<float>("fog", 0.001);
    useOptTexture = new Uniform<bool>("useOptTexture", false);
    AddUniform(m_textureSampler);
    AddUniform(m_optTextureSampler);
    AddUniform(m_material);
    AddUniform(dirLight);
    AddUniform(pointLight);
    AddUniform(spotLight);
    AddUniform(textureMat);
    AddUniform(fog);
    AddUniform(useOptTexture);
}

Object3DShaderContext::Object3DShaderContext(const String& mesh, const String& texture, const String& optTexture)
    : m_textureUnits(Vector<Shared<Texture>>({TextureManager::GetTexture(texture), TextureManager::GetTexture(optTexture)})), m_uniforms(Material())
{
    m_mesh = PrimitivesManager::GetPrimitives(mesh);
}

Object3DShaderContext::Object3DShaderContext(const String& mesh, const String& texture, const Material& material)
    : m_textureUnits(Vector<Shared<Texture>>({TextureManager::GetTexture(texture)})), m_uniforms(material)
{
    m_mesh = PrimitivesManager::GetPrimitives(mesh);
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
    uniforms.fog->value = GlobalSceneState::fog;
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


SunUniforms::SunUniforms() 
{ 
    m_textureSampler = new Uniform<int>("textureSampler", 0);
    time = new Uniform<float>("time", 0);
    fog = new Uniform<float>("fog", 0.001);
    AddUniform(m_textureSampler);
    AddUniform(time);
    AddUniform(fog);
}

SunShaderContext::SunShaderContext(const String& mesh, const String& texture)
    : m_textureUnits(Vector<Shared<Texture>>({TextureManager::GetTexture(texture)}))
{
    m_mesh = PrimitivesManager::GetPrimitives(mesh);
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
Line3DShaderContextUpdater::Line3DShaderContextUpdater(Line3DShaderContext* shaderContext)
    : m_shaderContext(shaderContext)
{

}
void Line3DShaderContextUpdater::Update()
{
    //GL(LineWidth(m_shaderContext->GetWidth()));
}

}