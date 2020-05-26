

#ifndef PGR_SHADER_CONTEXTS_HPP
#define PGR_SHADER_CONTEXTS_HPP

#include <core/render/ShaderContext.hpp>
#include <core/scene/Node.hpp>

namespace sadekpet {

struct Material
{

};

class Object3DUniforms : public Uniforms
{
private:
    Uniform<int>* m_textureSampler;
public:
    Object3DUniforms();
};

class Object3DShaderContext : public ShaderContext {
private:
    Shared<Primitives> m_mesh;
    Object3DUniforms m_uniforms;
    TextureUnits m_textureUnits;
public:
    Object3DShaderContext(const String& mesh, const String& texture);
    TypeIndex GetType() const override;
    const Shared<Primitives>& GetPrimitives() override;
    Uniforms& GetUniforms() override;
    TextureUnits& GetTextureUnits() override;
};

class Object3DShaderContextUpdater : public ShaderContextUpdater
{
private:
    Object3DShaderContext* m_shaderContext;
public:
    Object3DShaderContextUpdater(Object3DShaderContext* shaderContext);
    void Update() override;
};

class Basic3DUniforms : public Uniforms
{
private:
    Uniform<int>* m_textureSampler;
public:
    Basic3DUniforms();
};

class Basic3DShaderContext : public ShaderContext {
private:
    Shared<Primitives> m_mesh;
    Basic3DUniforms m_uniforms;
    TextureUnits m_textureUnits;
public:
    Basic3DShaderContext(const String& mesh, const String& texture);
    TypeIndex GetType() const override;
    const Shared<Primitives>& GetPrimitives() override;
    Uniforms& GetUniforms() override;
    TextureUnits& GetTextureUnits() override;
};

class Line3DUniforms : public Uniforms
{
public:
    Uniform<glm::vec3>* m_color;
public:
    Line3DUniforms(glm::vec3 color);
};

class Line3DShaderContext : public ShaderContext {
private:
    float m_width;
    Shared<Primitives> m_lines;
    Line3DUniforms m_uniforms;
    TextureUnits m_textureUnits;
public:
    Line3DShaderContext(Line3D* lines, float width, glm::vec3 color);
    TypeIndex GetType() const override;
    const Shared<Primitives>& GetPrimitives() override;
    Uniforms& GetUniforms() override;
    TextureUnits& GetTextureUnits() override;
    float GetWidth() const { return m_width; }
};

class Line3DShaderContextUpdater : public ShaderContextUpdater
{
private:
    Line3DShaderContext* m_shaderContext;
public:
    Line3DShaderContextUpdater(Line3DShaderContext* shaderContext);
    void Update() override;
};

}

#endif // PGR_SHADER_CONTEXTS_HPP