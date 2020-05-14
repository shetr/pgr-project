/**
 * @file ShaderManager.hpp
 * @author sadekpet
 * @brief 
 * 
 */

#ifndef PGR_SHADER_MANAGER_HPP
#define PGR_SHADER_MANAGER_HPP

#include <core/render/ShaderContext.hpp>
#include <core/render/Program.hpp>

namespace sadekpet {

class ShaderManager
{
private:
    static ShaderManager* s_instance;
    static String s_shadersPath;
    UnordMap<TypeIndex, Unique<GraphicsProgram>> m_renderPrograms;
public:
    static ShaderManager* Init();
    ~ShaderManager();
    static void AddRenderProgram(TypeIndex shaderContextType, String programName);
    static int BindRenderProgram(TypeIndex shaderContextType);
private:
    static void AddRenderProgram(TypeIndex shaderContextType, GraphicsProgram* program);
    static String ReadFile(String name);
    ShaderManager();
};

}

#endif // PGR_SHADER_MANAGER_HPP