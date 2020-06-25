#include "Framebuffer.hpp"

#include "OpenGL.hpp"

namespace sadekpet {

Framebuffer::Framebuffer() : m_id(0)
{
    glGenFramebuffers(1, &m_id);
}
Framebuffer::~Framebuffer()
{
    glDeleteFramebuffers(1, &m_id);
}
void Framebuffer::Bind() const
{
    glBindFramebuffer(GL_FRAMEBUFFER, m_id);
}
void Framebuffer::UnBind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
bool Framebuffer::IsComplete() const
{
    return glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE;
}

}