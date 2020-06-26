#include "Renderbuffer.hpp"

#include "OpenGL.hpp"

namespace sadekpet {


Renderbuffer::Renderbuffer() : m_id(0)
{
    GL(GenRenderbuffers(1, &m_id));
}
Renderbuffer::~Renderbuffer()
{
    GL(DeleteRenderbuffers(1, &m_id));
}
void Renderbuffer::Bind()
{
    GL(BindRenderbuffer(GL_RENDERBUFFER, m_id)); 
}
void Renderbuffer::UnBind()
{
    GL(BindRenderbuffer(GL_RENDERBUFFER, 0)); 
}
void Renderbuffer::StorageDephtStencil(int width, int height)
{
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
}

}