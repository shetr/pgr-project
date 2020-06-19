#include "ParticleSystem.hpp"

#include <core/manage/TextureManager.hpp>
#include <core/scene/Layers.hpp>
#include <algorithm>

#include <iostream>
#include <core/Console.hpp>

namespace sadekpet {

VertexLayout ParticleVertex::s_layout ({
    VertexElement(VertexType::FLOAT32, VertexElementCount::_3),
    VertexElement(VertexType::FLOAT32, VertexElementCount::_1),
    VertexElement(VertexType::FLOAT32, VertexElementCount::_1),
    VertexElement(VertexType::FLOAT32, VertexElementCount::_1)
});
const VertexLayout& ParticleVertex::GetLayout() {
    return s_layout;
}

struct ParticleCompare
{
public:
    bool operator()(const Particle& p1, const Particle& p2) {
        return p1.distance > p2.distance;
    }
};

ParticleSystemUniforms::ParticleSystemUniforms(glm::ivec2 textureSizes, glm::vec2 textureOffset)
{
    m_textureSampler = new Uniform<int>("textureSampler", 0);
    m_textureSizes = new Uniform<glm::ivec2>("textureSizes", textureSizes);
    m_textureOffset = new Uniform<glm::vec2>("textureOffset", textureOffset);
    AddUniform(m_textureSampler);
    AddUniform(m_textureSizes);
    AddUniform(m_textureOffset);
}

glm::vec2 ParticleSystemMesh::s_vertices[4] = {
    glm::vec2(-0.5f, -0.5f),
    glm::vec2( 0.5f, -0.5f), 
    glm::vec2( -0.5f, 0.5f),
    glm::vec2( 0.5f, 0.5f)
};
glm::vec2 ParticleSystemMesh::s_uvs[4] = {
    glm::vec2(0, 0),
    glm::vec2(1, 0), 
    glm::vec2(0, 1),
    glm::vec2(1, 1)
};

ParticleSystemMesh::ParticleSystemMesh(uint maxParticlesCount)
    : m_maxParticlesCount(maxParticlesCount), m_particlesCount(0)
{
    m_vericesBuffer = Shared<VertexBuffer<Vec2D>>(VertexBuffer<Vec2D>::Create(4, (Vec2D*)s_vertices));
    m_uvsBuffer = Shared<VertexBuffer<Vec2D>>(VertexBuffer<Vec2D>::Create(4, (Vec2D*)s_uvs));
    m_particlesBuffer = Shared<VertexBuffer<ParticleVertex>>(VertexBuffer<ParticleVertex>::CreateDynamic(maxParticlesCount));
    VertexArray* vertexArray = new VertexArray();
    vertexArray->AddVertexBuffer(m_vericesBuffer);
    vertexArray->AddVertexBuffer(m_uvsBuffer);
    vertexArray->AddVertexBuffer(m_particlesBuffer);
    for(VertexElement& element: vertexArray->GetLayouts()[2].Elements()) {
        element.SetDivisor(1);
    }
    m_vertexArray = Unique<VertexArray>(vertexArray);
    m_vertexArray->UnBind();
    m_vericesBuffer->UnBind();
    m_uvsBuffer->UnBind();
    m_particlesBuffer->UnBind();
}

void ParticleSystemMesh::Update(uint particlesCount, ParticleVertex* particles)
{
    m_particlesCount = particlesCount;
    m_particlesBuffer->UpdateData(particlesCount, particles);
}

void ParticleSystemMesh::BeforeDraw()
{
    m_vertexArray->SetDivisors();
}

ParticleSystemShaderContext::ParticleSystemShaderContext(const Shared<ParticleSystemMesh>& mesh, const String& texture, glm::ivec2 textureSizes, glm::vec2 textureOffset)
    : m_textureUnits(Vector<Shared<Texture>>({TextureManager::GetTexture(texture)})), m_uniforms(textureSizes, textureOffset), m_mesh(mesh), m_primitives(mesh)
{
}

void ParticleSystemShaderContext::BeforeDraw()
{
    m_mesh->BeforeDraw();
}

ParticleSystem::ParticleSystem(uint maxParticleCount, float dieSpeed, const String& texture, glm::ivec2 textureSizes, glm::vec2 textureOffset)
    : m_mesh(new ParticleSystemMesh(maxParticleCount)), m_shaderContext(m_mesh, texture, textureSizes, textureOffset), m_dieSpeed(dieSpeed),
      m_particles(maxParticleCount), m_outParticles(maxParticleCount), m_particlesCount(0), m_realParticlesCount(0)
{
}
void ParticleSystem::Spawn(const ParticleVertex& particle)
{
    m_spawnedParticles.push(particle);
}
void ParticleSystem::Update(float deltaTime)
{
    float dt = m_dieSpeed*deltaTime;
    glm::vec3 cameraPos = GetLayer()->GetCurrentCamera()->GetWorldPos();
    for(size_t i = 0; i < m_realParticlesCount; i++) {
        Particle& particle = m_particles[i];
        ParticleVertex& vert = particle.vert;
        if(vert.time < 1) {
            vert.time += dt;
        }
        if(vert.time >= 1 && !m_spawnedParticles.empty()) {
            vert = m_spawnedParticles.front();
            m_spawnedParticles.pop();
        }
        if(vert.time < 1) {
            particle.distance = glm::distance(cameraPos, vert.pos);
        }
    }
    if(m_spawnedParticles.empty()) {
        for(int i = m_realParticlesCount - 1; i >= 0; i--) {
            if(m_particles[i].vert.time >= 1) {
                m_realParticlesCount--;
            } else {
                break;
            }
        }
    } else {
        int replaceIdx = 0;
        while (!m_spawnedParticles.empty())
        {
            int idx;
            if(m_realParticlesCount < m_particles.size()) {
                idx = m_realParticlesCount;
                m_realParticlesCount++;
            } else {
                idx = replaceIdx;
                replaceIdx++;
            }
            Particle& particle = m_particles[idx];
            ParticleVertex& vert = particle.vert;
            vert = m_spawnedParticles.front();
            m_spawnedParticles.pop();
            particle.distance = glm::distance(cameraPos, vert.pos);
        }
    }
    
    ParticleCompare cmp;
    std::sort(m_particles.begin(), m_particles.begin() + m_realParticlesCount, cmp);
    uint particlesCount = 0;
    for(size_t i = 0; i < m_realParticlesCount; i++) {
        Particle& particle = m_particles[i];
        ParticleVertex& vert = particle.vert;
        if(vert.time < 1) {
            m_outParticles[particlesCount] = vert;
            particlesCount++;
        }
    }
    m_mesh->Update(particlesCount, m_outParticles.data());
}

}