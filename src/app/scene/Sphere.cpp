#include "Sphere.hpp"

#include <app/generate/MeshGen.hpp>

namespace sadekpet {

SphereShaderContext::SphereShaderContext()
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