/**
 * @file RectangleShaderData.hpp
 * @author sadekpet
 * @brief 
 * 
 */

#ifndef PGR_RECTANGLE_HPP
#define PGR_RECTANGLE_HPP

#include <core/render/Material.hpp>
#include <core/render/VertexTypes.hpp>
#include <core/scene/Node.hpp>

namespace sadekpet {

class Rectangle : public Mesh
{
private:
    Vec2D m_vertices[4];
    int m_indices[6];
    Shared<VertexBuffer<Vec2D>> m_vertexBuffer;
    Shared<IndexBuffer> m_indexBuffer;
    Shared<VertexArray> m_vertexArray;
public:
    Rectangle();
    const Shared<VertexArray>& GetVertexArray() override { return m_vertexArray; }
    PrimitiveType GetType() const override { return PrimitiveType::TRIANGLES; }
    int GetCount() const override { return 6; }
};

class RectangleUniforms : public Uniforms
{
private:
    Uniform<glm::vec3> m_color;
public:
    RectangleUniforms() : Uniforms(glm::mat4(1), glm::mat4(1), glm::mat4(1)), m_color("color", glm::vec3(1,1,0)) {}
    void SetColor(const glm::vec3& color) { m_color.value = color; }
protected:
    void SetUniformsImpl(int programID) override;
    void UpdateImpl() override;
};

class RectangleMaterial : public Material
{
private:
    Rectangle m_rectangle;
    RectangleUniforms m_uniforms;
    TextureUnits m_textureUnits = TextureUnits({});
public:
    RectangleMaterial() {}
    TypeIndex GetType() const override;
    Mesh& GetMesh() override;
    Uniforms& GetUniforms() override;
    TextureUnits& GetTextureUnits() override;
};

class RectangleNode : public VisibleNode
{
private:
    RectangleMaterial m_material;
public:
    RectangleNode() { m_material.GetUniforms().SetOwner(this); }
    Material& GetMaterial() override { return m_material; }
};

}

#endif // PGR_RECTANGLE_HPP