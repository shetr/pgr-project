#include "Sphere.hpp"

#include <app/generate/MeshGen.hpp>

#include <core/manage/TextureManager.hpp>

namespace sadekpet {

SphereShaderContext::SphereShaderContext()
    : m_textureUnits(Vector<Shared<Texture>>({TextureManager::GetTexture("sun")}))
{
    m_mesh = Shared<Primitives>(MeshGen::BasicSphere(20));
}

TypeIndex SphereShaderContext::GetType() const
{
    return TypeIndex(typeid(SphereShaderContext));
}
const Shared<Primitives>& SphereShaderContext::GetPrimitives()
{
    return m_mesh;
}
Uniforms& SphereShaderContext::GetUniforms()
{
    return m_uniforms;
}
TextureUnits& SphereShaderContext::GetTextureUnits()
{
    return m_textureUnits;
}

}