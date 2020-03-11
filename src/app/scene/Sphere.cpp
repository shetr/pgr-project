#include "Sphere.hpp"

#include <app/generate/MeshGen.hpp>

namespace sadekpet {

SphereMaterial::SphereMaterial()
{
    m_mesh = Shared<Primitives>(MeshGen::BasicSphere(20));
}

TypeIndex SphereMaterial::GetType() const
{
    return TypeIndex(typeid(SphereMaterial));
}
const Shared<Primitives>& SphereMaterial::GetPrimitives()
{
    return m_mesh;
}
Uniforms& SphereMaterial::GetUniforms()
{
    return m_uniforms;
}
TextureUnits& SphereMaterial::GetTextureUnits()
{
    return m_textureUnits;
}

}