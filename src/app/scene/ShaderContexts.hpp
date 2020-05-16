

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

}

#endif // PGR_SHADER_CONTEXTS_HPP