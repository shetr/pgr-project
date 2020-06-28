#include "Renderer.hpp"

#include "OpenGL.hpp"
#include <core/scene/Camera.hpp>

#include <core/effects/CopyEffect.hpp>
#include <core/effects/BlurEffect.hpp>
#include <core/effects/BloomEffect.hpp>

#include <iostream>

namespace sadekpet {

Renderer::Renderer()
{

}
Renderer::~Renderer()
{

}

void Renderer::SetClearColor(glm::vec4 color)
{
    GL(ClearColor(color.r, color.g, color.b, color.a));
}

void Renderer::Init()
{
    SetClearColor(glm::vec4(0, 0, 0, 1));
    GL(Enable(GL_MULTISAMPLE));
    GL(Enable(GL_BLEND));
    GL(BlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    GL(Enable(GL_DEPTH_TEST));
    GL(Enable(GL_STENCIL_TEST));
    GL(StencilOp(GL_KEEP, GL_KEEP, GL_REPLACE));
    GL(CullFace( GL_BACK));
    GL(Enable(GL_CULL_FACE));
    WindowSize winSize = Window::GetSize();
    GL(Viewport(0, 0, winSize.width, winSize.height));
    m_windowSizeHandler = std::make_unique<WindowSizeHandler>(this, &Renderer::OnWindowResize, Window::Get());
    
    m_offFramebuffer = Unique<Framebuffer>(new Framebuffer());
    m_offFramebuffer->Bind();
    m_offTexture = Shared<Texture2D>(new Texture2D(winSize.width, winSize.height, nullptr, TextureChanels::RGB));
    m_offTexture->Bind();
    m_offTexture->Init();
    GL(TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    GL(TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
    m_offFramebuffer->AttachTexture2D(m_offTexture, FramebufferColor::_0);
    m_offBrightTexture = Shared<Texture2D>(new Texture2D(winSize.width, winSize.height, nullptr, TextureChanels::RGB));
    m_offBrightTexture->Bind();
    m_offBrightTexture->Init();
    GL(TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    GL(TexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
    m_offFramebuffer->AttachTexture2D(m_offBrightTexture, FramebufferColor::_1);
    m_offRenderbuffer = Shared<Renderbuffer>(new Renderbuffer());
    m_offRenderbuffer->Bind();
    m_offRenderbuffer->StorageDephtStencil(winSize.width, winSize.height);
    m_offRenderbuffer->UnBind();
    m_offFramebuffer->AttachRenderbufferDepthStencil(m_offRenderbuffer);
    if(!m_offFramebuffer->IsComplete()) {
        std::cout << "offscreen framebuffer is not complete" << std::endl;
    }
    
    //m_effect = Unique<PostProcessingEffect>(new BlurEffect());
    m_effect = Unique<PostProcessingEffect>(new BloomEffect(winSize.width, winSize.height));
}

void Renderer::Clear()
{
    GL(ClearStencil(0));
    GL(Clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT));
}

void Renderer::ClearDepth()
{
    GL(Clear(GL_DEPTH_BUFFER_BIT));
}

void Renderer::DepthMask(bool enable)
{
    GL(DepthMask(enable));
}

void Renderer::SwapBuffers()
{
    glutSwapBuffers();
}

void Renderer::OnWindowResize(const WindowSizeEvent& event)
{
    WindowSize winSize = Window::GetSize();
    GL(Viewport(0, 0, winSize.width, winSize.height));
    for(Camera* camera: Camera::Cameras()) {
        camera->Resize();
    }
    m_offRenderbuffer->Bind();
    m_offRenderbuffer->StorageDephtStencil(winSize.width, winSize.height);
    m_offRenderbuffer->UnBind();
    m_offTexture->Bind();
    m_offTexture->Resize(winSize.width, winSize.height);
    m_offBrightTexture->Bind();
    m_offBrightTexture->Resize(winSize.width, winSize.height);

    m_effect->Resize(winSize.width, winSize.height);
}

void Renderer::SetStencilID(uint8_t id)
{
    GL(StencilFunc(GL_ALWAYS, id, -1));
}

void Renderer::Draw(ShaderContext& shaderContext)
{
    int programID = ShaderManager::BindRenderProgram(shaderContext.GetType());
    const Shared<Primitives>& primitives = shaderContext.GetPrimitives();
    primitives->Bind();
    shaderContext.GetTextureUnits().Activate();
    Uniforms& uniforms = shaderContext.GetUniforms();
    uniforms.SetUniforms(programID);
    shaderContext.DrawFunction();
    VertexArray::UnBind();
    GraphicsProgram::UnBind();
}


void Renderer::StartScene()
{
    //m_offFramebuffer->UnBind();
    m_offFramebuffer->Bind();
    unsigned int attachments[2] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 };
    GL(DrawBuffers(2, attachments));
}
void Renderer::EndScene()
{
    
    m_offFramebuffer->UnBind();
    GL(Disable(GL_DEPTH_TEST));
    GL(Clear(GL_COLOR_BUFFER_BIT));
    m_effect->Run(m_offTexture, m_offBrightTexture);
    //m_effect->Run(m_offTexture);
    GL(Enable(GL_DEPTH_TEST));
}

}
