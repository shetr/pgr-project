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
    glm::vec3 pos;
    float size;
    float rot;
    float time;
private:
    static VertexLayout s_layout;
public:
    static const VertexLayout& GetLayout();
    ParticleVertex() 
        : ParticleVertex(glm::vec3(0,0,0), 1, 0, 2) {}
    ParticleVertex(glm::vec3 p, float s, float r, float t)
        : pos(p), size(s), rot(r), time(t) {}
};

struct Particle
{
    ParticleVertex vert;
    float distance;
public:
    Particle() : vert(), distance(-1) {}
};

class ParticleSystemUniforms : public Uniforms
{
private:
    Uniform<int>* m_textureSampler;
    Uniform<glm::ivec2>* m_textureSizes;
    Uniform<glm::vec2>* m_textureOffset;
public:
    ParticleSystemUniforms(glm::ivec2 textureSizes, glm::vec2 textureOffset);
};

class ParticleSystemMesh : public Primitives
{
protected:
    static glm::vec2 s_vertices[4];
    static glm::vec2 s_uvs[4];
    Shared<VertexBuffer<Vec2D>> m_vericesBuffer;
    Shared<VertexBuffer<Vec2D>> m_uvsBuffer;
    Shared<VertexBuffer<ParticleVertex>> m_particlesBuffer;
    uint m_maxParticlesCount;
    uint m_particlesCount;
public:
    ParticleSystemMesh(uint maxParticlesCount);
    virtual PrimitiveType GetType() const override { return PrimitiveType::TRIANGLE_STRIP; }
    virtual int GetCount() const override { return 4; }
    uint GetParticlesCount() const { return m_particlesCount; }
    void Update(uint particlesCount, ParticleVertex* particles);
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
    ParticleSystemShaderContext(const Shared<ParticleSystemMesh>& mesh, const String& texture, glm::ivec2 textureSizes, glm::vec2 textureOffset);

    TypeIndex GetType() const override{
        return TypeIndex(typeid(ParticleSystemShaderContext));
    }
    const Shared<Primitives>& GetPrimitives() override{
        return m_primitives;
    }
    Uniforms& GetUniforms() override{
        return m_uniforms;
    }
    ParticleSystemUniforms& GetParticleSystemUniforms() {
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
    Vector<Particle> m_particles;
    Vector<ParticleVertex> m_outParticles;
    uint m_particlesCount;
    uint m_realParticlesCount;
    Queue<ParticleVertex> m_spawnedParticles;
    float m_dieSpeed;
public:
    ParticleSystem(uint maxParticleCount, float dieSpeed, const String& texture, glm::ivec2 textureSizes, glm::vec2 textureOffset);
    void Spawn(const ParticleVertex& particle);
    void Update(float deltaTime) override;
    ShaderContext& GetShaderContext() override { return m_shaderContext; }
};

}

#endif // PGR_PARTICLE_SYSTEM_HPP