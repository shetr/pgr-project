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
#include <core/render/Material.hpp>

namespace sadekpet {

class SphereMaterial : public Material {
private:
    Shared<Primitives> m_mesh;
    Uniforms m_uniforms;
    TextureUnits m_textureUnits = TextureUnits({});
public:
    SphereMaterial();
    TypeIndex GetType() const override;
    const Shared<Primitives>& GetPrimitives() override;
    Uniforms& GetUniforms() override;
    TextureUnits& GetTextureUnits() override;
};

class SphereNode : public VisibleNode{
private:
    SphereMaterial m_material;
public:
    SphereNode() { m_material.GetUniforms().SetOwner(this); }
    Material& GetMaterial() override { return m_material; }
};

}

#endif // PGR_SHPERE_HPP