#include "Program.hpp"

#include "OpenGL.hpp"

#include <iostream>

namespace sadekpet
{

GraphicsProgram::GraphicsProgram(GraphicsProgram&& old)
{
    m_id = old.m_id;
    old.m_id = 0;
}

GraphicsProgram& GraphicsProgram::operator=(GraphicsProgram&& old)
{
    m_id = old.m_id;
    old.m_id = 0;
    return *this;
}

GraphicsProgram::~GraphicsProgram()
{
    GL(DeleteProgram(m_id));
}

void GraphicsProgram::Bind() const
{
    GL(UseProgram(m_id));
}

void GraphicsProgram::UnBind()
{
    GL(UseProgram(0));
}

GraphicsProgramLinker::GraphicsProgramLinker() : m_shaders() {}

Opt<GraphicsProgram*> GraphicsProgramLinker::Link()
{
    uint programId = GL(CreateProgram());
    for(Shader const* shader: m_shaders){
        GL(AttachShader(programId, shader->GetId()));
    }
    GL(LinkProgram(programId));

    int isLinked = 0;
    GL(GetProgramiv(programId, GL_LINK_STATUS, &isLinked));
    if (!isLinked)
    {
        int maxLength = 0;
        GL(GetProgramiv(programId, GL_INFO_LOG_LENGTH, &maxLength));
        std::vector<char> infoLog(maxLength + 1);
        GL(GetProgramInfoLog(programId, maxLength, &maxLength, &infoLog[0]));
        infoLog[maxLength] = 0;
        std::cout << "Linking error: " << &infoLog[0] << std::endl;
        
        return {};
    }
    
    for (Shader const* shader: m_shaders) {
        GL(DetachShader(programId, shader->GetId()));
    }
    return new GraphicsProgram(programId);
}

void RenderProgramLinker::AddShader(const RenderShader& shader)
{
    m_shaders.push_back(&shader);
}

void ComputeProgramLinker::AddShader(const ComputeShader& shader)
{
    m_shaders.push_back(&shader);
}

}