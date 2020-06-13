/**
 * @file ParticleSystem.hpp
 * @author sadekpet (sadekpet@fel.cvut.cz)
 * @brief 
 * @date 2020-06-13
 * 
 */

#ifndef PGR_PARTICLE_SYSTEM_HPP
#define PGR_PARTICLE_SYSTEM_HPP

#include <core/render/ShaderContext.hpp>
#include <core/scene/Node.hpp>

namespace sadekpet {

struct ParticleVertex
{
    glm::vec3 pos = glm::vec3(0,0,0);
    float size = 1;
    float time = 0;
private:
    static VertexLayout s_layout;
public:
    static const VertexLayout& GetLayout();
};

struct Particle
{
    ParticleVertex vert;
    float distance = 0;
};

class ParticleSystemUniforms : public Uniforms
{
};

class ParticleSystemMesh : public Primitives
{
protected:
    static glm::vec2 s_vertices[4];
    Shared<VertexBuffer<Vec2D>> m_vericesBuffer;
    Shared<VertexBuffer<ParticleVertex>> m_particlesBuffer;
    uint m_maxParticlesCount;
    uint m_particlesCount;
public:
    ParticleSystemMesh(uint maxParticlesCount);
    virtual PrimitiveType GetType() const override { return PrimitiveType::TRIANGLE_STRIP; }
    virtual int GetCount() const override { return 4; }
    uint GetParticlesCount() const { return m_particlesCount; }
    void Update(const Vector<ParticleVertex>& particles);
    void BeforeDraw();
};

class ParticleSystemShaderContext : public InstancedShaderContext
{
private:
    Shared<ParticleSystemMesh> m_mesh;
    Shared<Primitives> m_primitives;
    ParticleSystemUniforms m_uniforms;
    TextureUnits m_textureUnits;
public:
    ParticleSystemShaderContext(const Shared<ParticleSystemMesh>& mesh, const String& texture);

    TypeIndex GetType() const override{
        return TypeIndex(typeid(ParticleSystemShaderContext));
    }
    const Shared<Primitives>& GetPrimitives() override{
        return m_primitives;
    }
    Uniforms& GetUniforms() override{
        return m_uniforms;
    }
    TextureUnits& GetTextureUnits() override{
        return m_textureUnits;
    }
    uint GetVertexCount() const override { return m_mesh->GetCount(); }
    uint GetInstanceCount() const override { return m_mesh->GetParticlesCount(); }
protected:
    void BeforeDraw() override;
};

class ParticleSystem : public VisibleNode
{
private:
    Shared<ParticleSystemMesh> m_mesh;
    ParticleSystemShaderContext m_shaderContext;
    Vector<ParticleVertex> m_particles;
public:
    ParticleSystem(uint maxParticleCount, const String& texture);
    void Spawn(ParticleVertex particle);
    void Update(float deltaTime) override;
    ShaderContext& GetShaderContext() override { return m_shaderContext; }
};

}

#endif // PGR_PARTICLE_SYSTEM_HPP