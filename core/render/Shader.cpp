#include "Shader.hpp"

#include "OpenGL.hpp"
#include <iostream>

namespace sadekpet
{

Shader::Shader() : m_id(0) {}

Shader::~Shader()
{
    if(m_id != 0) {
        GL(DeleteShader(m_id));
    }
}

Shader::Shader(Shader&& shader) : m_id(shader.m_id)
{
    shader.m_id = 0;
}

Shader& Shader::operator=(Shader&& shader)
{
    m_id = shader.m_id;
    shader.m_id = 0;
    return (*this);
}

bool Shader::Compile(const String& source)
{
    const char* cSource = source.c_str();
    GL(ShaderSource(m_id, 1, &cSource, 0));
    GL(CompileShader(m_id));

    int isCompiled = 0;
    GL(GetShaderiv(m_id, GL_COMPILE_STATUS, &isCompiled));
    if (!isCompiled)
    {
        int maxLength = 0;
        GL(GetShaderiv(m_id, GL_INFO_LOG_LENGTH, &maxLength));
        std::vector<char> infoLog(maxLength + 1);
        GL(GetShaderInfoLog(m_id, maxLength, &maxLength, &infoLog[0]));
        infoLog[maxLength] = 0;
        std::cout << "Compile error: " << &infoLog[0] << std::endl;

        GL(DeleteShader(m_id));
        return false;
    }
    return true;
}

Opt<VertexShader> Shader::CompileVertexShader(const String& source)
{
    VertexShader shader;
    shader.Init();
    if(shader.Compile(source)) return shader; return {};
}
Opt<FragmentShader> Shader::CompileFragmentShader(const String& source)
{
    FragmentShader shader;
    shader.Init();
    if(shader.Compile(source)) return shader; return {};
}
Opt<GeometryShader> Shader::CompileGeometryShader(const String& source)
{
    GeometryShader shader;
    shader.Init();
    if(shader.Compile(source)) return shader; return {};
}
Opt<TessEvaluationShader> Shader::CompileTessEvaluationShader(const String& source)
{
    TessEvaluationShader shader;
    shader.Init();
    if(shader.Compile(source)) return shader; return {};
}
Opt<TessControlShader> Shader::CompileTessControlShader(const String& source)
{
    TessControlShader shader;
    shader.Init();
    if(shader.Compile(source)) return shader; return {};
}
Opt<ComputeShader> Shader::CompileComputeShader(const String& source)
{
    ComputeShader shader;
    shader.Init();
    if(shader.Compile(source)) return shader; return {};
}

void Shader::Init()
{
    m_id = GL(CreateShader(static_cast<uint>(GetType())));
}


}