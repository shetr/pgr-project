#include "Renderer.hpp"

#include "OpenGL.hpp"
#include <core/scene/Camera.hpp>

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
    GL(CullFace( GL_BACK));
    GL(Enable(GL_CULL_FACE));
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
    for(Camera* camera: Camera::Cameras()) {
        camera->Resize();
    }
}

void Renderer::Draw(ShaderContext& shaderContext)
{
    int programID = ShaderManager::BindRenderProgram(shaderContext.GetType());
    const Shared<Primitives>& primitives = shaderContext.GetPrimitives();
    primitives->Bind();
    shaderContext.GetTextureUnits().Activate();
    Uniforms& uniforms = shaderContext.GetUniforms();
    uniforms.SetUniforms(programID);
    GL(DrawElements(static_cast<uint>(primitives->GetType()), primitives->GetCount(), GL_UNSIGNED_INT, 0));
    VertexArray::UnBind();
    GraphicsProgram::UnBind();
}

}
