#include "Framebuffer.hpp"

#include "OpenGL.hpp"

namespace sadekpet {

Framebuffer::Framebuffer() : m_id(0)
{
    GL(GenFramebuffers(1, &m_id));
}
Framebuffer::~Framebuffer()
{
    GL(DeleteFramebuffers(1, &m_id));
}
void Framebuffer::Bind() const
{
    GL(BindFramebuffer(GL_FRAMEBUFFER, m_id));
}
void Framebuffer::UnBind()
{
    GL(BindFramebuffer(GL_FRAMEBUFFER, 0));
}
bool Framebuffer::IsComplete() const
{
    uint res = GL(CheckFramebufferStatus(GL_FRAMEBUFFER));
    return res == GL_FRAMEBUFFER_COMPLETE;
}
void Framebuffer::AttachTexture2D(const Shared<Texture2D>& texture, FramebufferColor attachment)
{
    GL(FramebufferTexture2D(GL_FRAMEBUFFER, static_cast<uint>(attachment), GL_TEXTURE_2D, texture->GetID(), 0));
}
void Framebuffer::AttachRenderbufferDepthStencil(const Shared<Renderbuffer>& renderbuffer)
{
    GL(FramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderbuffer->GetID()));
}

}