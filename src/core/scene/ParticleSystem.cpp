#include "ParticleSystem.hpp"

#include <core/manage/TextureManager.hpp>

namespace sadekpet {

VertexLayout ParticleVertex::s_layout ({
    VertexElement(VertexType::FLOAT32, VertexElementCount::_3),
    VertexElement(VertexType::FLOAT32, VertexElementCount::_1),
    VertexElement(VertexType::FLOAT32, VertexElementCount::_1)
});
const VertexLayout& ParticleVertex::GetLayout() {
    return s_layout;
}


glm::vec2 ParticleSystemMesh::s_vertices[4] = {
    glm::vec2(-0.5f, -0.5f),
    glm::vec2( 0.5f, -0.5f), 
    glm::vec2( -0.5f, 0.5f),
    glm::vec2( 0.5f, 0.5f)
};

ParticleSystemMesh::ParticleSystemMesh(uint maxParticlesCount)
    : m_maxParticlesCount(maxParticlesCount), m_particlesCount(0)
{
    m_vericesBuffer = Shared<VertexBuffer<Vec2D>>(VertexBuffer<Vec2D>::Create(4, (Vec2D*)s_vertices));
    m_particlesBuffer = Shared<VertexBuffer<ParticleVertex>>(VertexBuffer<ParticleVertex>::CreateDynamic(maxParticlesCount));
    VertexArray* vertexArray = new VertexArray();
    vertexArray->AddVertexBuffer(m_vericesBuffer);
    vertexArray->AddVertexBuffer(m_particlesBuffer);
    for(VertexElement& element: vertexArray->GetLayouts()[1].Elements()) {
        element.SetDivisor(1);
    }
    m_vertexArray = Unique<VertexArray>(vertexArray);
    m_vertexArray->UnBind();
    m_vericesBuffer->UnBind();
    m_particlesBuffer->UnBind();
}

void ParticleSystemMesh::Update(const Vector<ParticleVertex>& particles)
{
    m_particlesCount = particles.size();
    m_particlesBuffer->UpdateData(particles.size(), particles.data());
}

void ParticleSystemMesh::BeforeDraw()
{
    m_vertexArray->SetDivisors();
}

ParticleSystemShaderContext::ParticleSystemShaderContext(const Shared<ParticleSystemMesh>& mesh, const String& texture)
    : m_textureUnits(Vector<Shared<Texture>>({TextureManager::GetTexture(texture)})), m_mesh(mesh), m_primitives(mesh)
{
}

void ParticleSystemShaderContext::BeforeDraw()
{
    m_mesh->BeforeDraw();
}

ParticleSystem::ParticleSystem(uint maxParticleCount, const String& texture)
    : m_mesh(new ParticleSystemMesh(maxParticleCount)), m_shaderContext(m_mesh, texture)
{
}
void ParticleSystem::Spawn(ParticleVertex particle)
{
    m_particles.push_back(particle);
    m_mesh->Update(m_particles);
}
void ParticleSystem::Update(float deltaTime)
{

}

}