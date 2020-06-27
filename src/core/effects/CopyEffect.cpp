#include "CopyEffect.hpp"

#include <core/manage/ShaderManager.hpp>

#include <core/render/OpenGL.hpp>

namespace sadekpet {

CopyEffect::CopyEffect() : PostProcessingEffect()
{
    m_textureSampler = new Uniform<int>("textureSampler", 0);
}

void CopyEffect::Run(Shared<Texture2D>& frame)
{
    int programID = ShaderManager::BindRenderProgram(TypeIndex(typeid(CopyEffect)));
    m_windowQuad->Bind();
    frame->Activate(TextureUnit::_0);
    frame->Bind();
    m_textureSampler->Set(programID);
    GL(DrawElements(static_cast<uint>(m_windowQuad->GetType()), m_windowQuad->GetCount(), GL_UNSIGNED_INT, 0));
    VertexArray::UnBind();
    GraphicsProgram::UnBind();
}

}