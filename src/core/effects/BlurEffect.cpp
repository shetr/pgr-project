#include "BlurEffect.hpp"

#include <core/manage/ShaderManager.hpp>

#include <core/render/OpenGL.hpp>

namespace sadekpet {


BlurEffect::BlurEffect() : PostProcessingEffect()
{
    m_texture1Sampler = new Uniform<int>("texture1Sampler", 0);
    m_texture2Sampler = new Uniform<int>("texture2Sampler", 1);
}

void BlurEffect::Run(Shared<Texture2D>& tex1, Shared<Texture2D>& tex2)
{
    int programID = ShaderManager::BindRenderProgram(TypeIndex(typeid(BlurEffect)));
    m_windowQuad->Bind();
    tex1->Activate(TextureUnit::_0);
    tex1->Bind();
    tex2->Activate(TextureUnit::_1);
    tex2->Bind();
    m_texture1Sampler->Set(programID);
    m_texture2Sampler->Set(programID);
    GL(DrawElements(static_cast<uint>(m_windowQuad->GetType()), m_windowQuad->GetCount(), GL_UNSIGNED_INT, 0));
    VertexArray::UnBind();
    GraphicsProgram::UnBind();
}

}