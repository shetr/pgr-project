

#ifndef PGR_SHADER_CONTEXTS_HPP
#define PGR_SHADER_CONTEXTS_HPP

#include <core/render/ShaderContext.hpp>
#include <core/scene/Node.hpp>
#include <core/render/Material.hpp>
#include <core/render/Light.hpp>

namespace sadekpet {

/**
 * @brief UniformStruct pro update materiálu do shaderu.
 */
class MaterialUniform : public UniformStruct
{
private:
    Uniform<glm::vec3>* m_ambient;
    Uniform<glm::vec3>* m_diffuse;
    Uniform<glm::vec3>* m_specular;
    Uniform<glm::vec3>* m_emission;
    Uniform<float>* m_shinines;
public:
    MaterialUniform(const String name) : MaterialUniform(name, Material()) {}
    MaterialUniform(const String name, const Material& material) : UniformStruct(name) {
        m_ambient = AddUniform("ambient", material.ambient);
        m_diffuse = AddUniform("diffuse", material.diffuse);
        m_specular = AddUniform("specular", material.specular);
        m_emission = AddUniform("emission", material.emission);
        m_shinines = AddUniform("shinines", material.shinines);
    }

    void UpdateMaterial(const Material& material) {
        m_ambient->value = material.ambient;
        m_diffuse->value = material.diffuse;
        m_specular->value = material.specular;
        m_emission->value = material.emission;
        m_shinines->value = material.shinines;
    }

};

/**
 * @brief UniformStruct pro update stavu světla do shaderu.
 */
class LightUniform : public UniformStruct
{
private:
    Uniform<LightType>* m_lightType;
    Uniform<glm::vec4>* m_position;
    Uniform<glm::vec3>* m_ambient;
    Uniform<glm::vec3>* m_diffuse;
    Uniform<glm::vec3>* m_specular;
    Uniform<glm::vec3>* m_spotDir;
    Uniform<float>* m_spotExponent;
    Uniform<float>* m_spotCutoff;
    Uniform<float>* m_attenuationConst;
    Uniform<float>* m_attenuationLin;
public:
    LightUniform(const String name) : LightUniform(name, Light()) {}
    LightUniform(const String name, const Light& light) : UniformStruct(name) {
        m_lightType = AddUniform("lightType", light.lightType);
        m_position = AddUniform("position", light.position);
        m_ambient = AddUniform("ambient", light.ambient);
        m_diffuse = AddUniform("diffuse", light.diffuse);
        m_specular = AddUniform("specular", light.specular);
        m_spotDir = AddUniform("spotDir", light.spotDir);
        m_spotExponent = AddUniform("spotExponent", light.spotExponent);
        m_spotCutoff = AddUniform("spotCutoff", light.spotCutoff);
        m_attenuationConst = AddUniform("attenuationConst", light.attenuationConst);
        m_attenuationLin = AddUniform("attenuationLin", light.attenuationLin);
    }
    void UpdateLight(const Light& light) {
        m_lightType->value = light.lightType;
        m_position->value = light.position;
        m_ambient->value = light.ambient;
        m_diffuse->value = light.diffuse;
        m_specular->value = light.specular;
        m_spotDir->value = light.spotDir;
        m_spotExponent->value = light.spotExponent;
        m_spotCutoff->value = light.spotCutoff;
        m_attenuationConst->value = light.attenuationConst;
        m_attenuationLin->value = light.attenuationLin;
    }
};

/**
 * @brief Uniforms pro object3D shader.
 */
class Object3DUniforms : public Uniforms
{
private:
    Uniform<int>* m_textureSampler;
    Uniform<int>* m_optTextureSampler;
    MaterialUniform* m_material;
public:
    LightUniform* dirLight;
    LightUniform* pointLight;
    LightUniform* spotLight;
    Uniform<glm::mat3>* textureMat;
    Uniform<float>* fog;
    Uniform<bool>* useOptTexture;
    Object3DUniforms(const Material& material);
};

/**
 * @brief ShaderContext pro object3D shader.
 */
class Object3DShaderContext : public ShaderContext {
private:
    Shared<Primitives> m_mesh;
    Object3DUniforms m_uniforms;
    TextureUnits m_textureUnits;
public:
    Object3DShaderContext(const String& mesh, const String& texture)
        : Object3DShaderContext(mesh, texture, Material()) {}
    Object3DShaderContext(const String& mesh, const String& texture, const String& optTexture);
    Object3DShaderContext(const String& mesh, const String& texture, const Material& material);
    Object3DUniforms& GetObject3DUniforms() { return m_uniforms; }
    TypeIndex GetType() const override{
        return TypeIndex(typeid(Object3DShaderContext));
    }
    const Shared<Primitives>& GetPrimitives() override{
        return m_mesh;
    }
    Uniforms& GetUniforms() override{
        return m_uniforms;
    }
    TextureUnits& GetTextureUnits() override{
        return m_textureUnits;
    }
};

/**
 * @brief ShaderContextUpdater pro object3D shader.
 */
class Object3DShaderContextUpdater : public ShaderContextUpdater
{
private:
    Object3DShaderContext* m_shaderContext;
public:
    Object3DShaderContextUpdater(Object3DShaderContext* shaderContext);
    Object3DUniforms& GetUniforms() { return m_shaderContext->GetObject3DUniforms(); }
    void Update() override;
};

/**
 * @brief Uniforms pro basic3D shader.
 */
class Basic3DUniforms : public Uniforms
{
private:
    Uniform<int>* m_textureSampler;
public:
    Basic3DUniforms();
};

/**
 * @brief ShaderContext pro basic3D shader.
 */
class Basic3DShaderContext : public ShaderContext {
private:
    Shared<Primitives> m_mesh;
    Basic3DUniforms m_uniforms;
    TextureUnits m_textureUnits;
public:
    Basic3DShaderContext(const String& mesh, const String& texture);
    TypeIndex GetType() const override {
        return TypeIndex(typeid(Basic3DShaderContext));
    }
    const Shared<Primitives>& GetPrimitives() override{
        return m_mesh;
    }
    Uniforms& GetUniforms() override{
        return m_uniforms;
    }
    TextureUnits& GetTextureUnits() override{
        return m_textureUnits;
    }
};


/**
 * @brief Uniforms pro sun shader.
 */
class SunUniforms : public Uniforms
{
private:
    Uniform<int>* m_textureSampler;
public:
    Uniform<float>* time;
    Uniform<float>* fog;
    SunUniforms();
};

/**
 * @brief ShaderContext pro sun shader.
 */
class SunShaderContext : public ShaderContext {
private:
    Shared<Primitives> m_mesh;
    SunUniforms m_uniforms;
    TextureUnits m_textureUnits;
public:
    SunShaderContext(const String& mesh, const String& texture);
    SunUniforms& GetSunUniforms() {return m_uniforms;}
    TypeIndex GetType() const override {
        return TypeIndex(typeid(SunShaderContext));
    }
    const Shared<Primitives>& GetPrimitives() override {
        return m_mesh;
    }
    Uniforms& GetUniforms() override {
        return m_uniforms;
    }
    TextureUnits& GetTextureUnits() override {
        return m_textureUnits;
    }
};

/**
 * @brief Uniforms pro line3D shader.
 */
class Line3DUniforms : public Uniforms
{
public:
    Uniform<glm::vec3>* m_color;
public:
    Line3DUniforms(glm::vec3 color);
};

/**
 * @brief ShaderContext pro line3D shader.
 */
class Line3DShaderContext : public ShaderContext {
private:
    float m_width;
    Shared<Primitives> m_lines;
    Line3DUniforms m_uniforms;
    TextureUnits m_textureUnits;
public:
    Line3DShaderContext(Line3D* lines, float width, glm::vec3 color);
    TypeIndex GetType() const override{
        return TypeIndex(typeid(Line3DShaderContext));
    }
    const Shared<Primitives>& GetPrimitives() override{
        return m_lines;
    }
    Uniforms& GetUniforms() override{
        return m_uniforms;
    }
    TextureUnits& GetTextureUnits() override{
        return m_textureUnits;
    }
    float GetWidth() const { return m_width; }
};

/**
 * @brief ShaderContextUpdater pro line3D shader.
 */
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