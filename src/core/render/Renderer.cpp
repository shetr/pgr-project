#include "Renderer.hpp"

#include "OpenGL.hpp"

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
    GL(Enable(GL_DEPTH_TEST));
    WindowSize winSize = Window::GetSize();
    GL(Viewport(0, 0, winSize.width, winSize.height));
    m_windowSizeHandler = std::make_unique<WindowSizeHandler>(this, &Renderer::OnWindowResize, Window::Get());
}

void Renderer::Clear()
{
    GL(Clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

void Renderer::SwapBuffers()
{
    glutSwapBuffers();
}

void Renderer::OnWindowResize(const WindowSizeEvent& event)
{
    WindowSize winSize = Window::GetSize();
    GL(Viewport(0, 0, winSize.width, winSize.height));
}

void Renderer::Draw(Material& material)
{
    int programID = ShaderManager::BindRenderProgram(material.GetType());
    Primitives& primitives = material.GetPrimitives();
    const Shared<VertexArray>& vertexArray = primitives.GetVertexArray();
    vertexArray->Bind();
    material.GetTextureUnits().Activate();
    Uniforms& uniforms = material.GetUniforms();
    uniforms.Update();
    uniforms.SetUniforms(programID);
    GL(DrawElements(static_cast<uint>(primitives.GetType()), primitives.GetCount(), GL_UNSIGNED_INT, 0));
    VertexArray::UnBind();
    GraphicsProgram::UnBind();
}

}
