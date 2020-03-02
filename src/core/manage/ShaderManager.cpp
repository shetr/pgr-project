#include "ShaderManager.hpp"

#include <iostream>

#include <stdio.h>
#include <stdlib.h>
#include <fstream>

namespace sadekpet {

ShaderManager* ShaderManager::s_instance = nullptr;
String ShaderManager::s_shadersPath = "res/shaders/";

ShaderManager* ShaderManager::Init()
{
    if(s_instance == nullptr) {
        s_instance = new ShaderManager();
    }
    return s_instance;
}
ShaderManager::~ShaderManager()
{
    s_instance = nullptr;
}
void ShaderManager::AddRenderProgram(TypeIndex materialType, String programName)
{
    String vertName = s_shadersPath+programName+".vert";
    String fragName = s_shadersPath+programName+".frag";
    String vertSrc = ReadFile(vertName);
    String fragSrc = ReadFile(fragName);

    RenderProgramLinker linker;
    Opt<VertexShader> vertShader = Shader::CompileVertexShader(vertSrc);
    if(vertShader.has_value()) {
        linker.AddShader(vertShader.value());
    } else {
        std::cout << "Vertex shader failed to compile" << std::endl;
        return;
    }
    Opt<FragmentShader> fragShader = Shader::CompileFragmentShader(fragSrc);
    if(fragShader.has_value()) {
        linker.AddShader(fragShader.value());
    } else {
        std::cout << "Fragment shader failed to compile" << std::endl;
        return;
    }
    Opt<GraphicsProgram*> gpuProgram = linker.Link();
    if(gpuProgram.has_value()){
        AddRenderProgram(materialType, gpuProgram.value());
    } else {
        std::cout << "Shaders linking failed" << std::endl;
        return;
    }
}
int ShaderManager::BindRenderProgram(TypeIndex materialType)
{
    UnordMap<TypeIndex, Unique<GraphicsProgram>>::iterator it = s_instance->m_renderPrograms.find(materialType);
    if(it != s_instance->m_renderPrograms.end()) {
        it->second->Bind();
        return it->second->GetID();
    } else {
        std::cout << "Shader data type not supported" << std::endl;
        return 0;
    }
}

void ShaderManager::AddRenderProgram(TypeIndex materialType, GraphicsProgram* program)
{
    s_instance->m_renderPrograms[materialType] = Unique<GraphicsProgram>(program);
}
String ShaderManager::ReadFile(String name)
{
    FILE *file = fopen(name.c_str(), "r");
    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    std::vector<char> res(fileSize + 1);
    fread(res.data(), 1, fileSize, file);
    fclose(file);
    res[fileSize] = 0;
    return String(res.data());
}
ShaderManager::ShaderManager()
{
}

}