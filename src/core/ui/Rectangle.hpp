/**
 * @file RectangleShaderData.hpp
 * @author sadekpet
 * @brief 
 * 
 */

#ifndef PGR_RECTANGLE_HPP
#define PGR_RECTANGLE_HPP

#include <core/render/ShaderContext.hpp>
#include <core/render/VertexTypes.hpp>
#include <core/scene/Node.hpp>

namespace sadekpet {

class Rectangle : public Primitives
{
private:
    Vec2D m_vertices[4];
    int m_indices[6];
    Unique<VertexBuffer<Vec2D>> m_vertexBuffer;
    Unique<IndexBuffer> m_indexBuffer;
public:
    Rectangle();
    PrimitiveType GetType() const override { return PrimitiveType::TRIANGLES; }
    int GetCount() const override { return 6; }
};

class RectangleUniforms : public Uniforms
{
private:
    Uniform<glm::vec3>* m_color;
public:
    RectangleUniforms();
    void SetColor(const glm::vec3& color) { m_color->value = color; }
};

class RectangleShaderContext : public ShaderContext
{
private:
    Shared<Primitives> m_rectangle = Shared<Primitives>(new Rectangle());
    RectangleUniforms m_uniforms;
    TextureUnits m_textureUnits = TextureUnits({});
public:
    RectangleShaderContext() { }
    TypeIndex GetType() const override;
    const Shared<Primitives>& GetPrimitives() override;
    Uniforms& GetUniforms() override;
    TextureUnits& GetTextureUnits() override;
};

class RectangleNode : public VisibleNode
{
private:
    RectangleShaderContext m_shaderContext;
public:
    RectangleNode() {}
    ShaderContext& GetShaderContext() override { return m_shaderContext; }
};

}

#endif // PGR_RECTANGLE_HPP