/**
 * @file Shader.hpp
 * @author sadekpet 
 * @brief 
 * 
 */

#ifndef PGR_SHADER_HPP
#define PGR_SHADER_HPP

#include <core/types.hpp>

namespace sadekpet
{

enum class ShaderType : uint
{
    FRAGMENT = 0x8B30,
    VERTEX = 0x8B31,
    GEOMETRY = 0x8DD9,
    TESS_EVALUATION = 0x8E87,
    TESS_CONTROL = 0x8E88,
    COMPUTE = 0x91B9
};

class VertexShader;
class FragmentShader;
class GeometryShader;
class TessEvaluationShader;
class TessControlShader;
class ComputeShader;

class Shader
{
private:
    uint m_id;
protected:
    Shader();

    bool Compile(const String& source);
public:
    Shader(const Shader& shader) = delete;
    Shader(Shader&& shader);
    Shader& operator=(Shader&& shader);
    virtual ~Shader();
    virtual ShaderType GetType() = 0;
    inline uint GetId() const { return m_id; } 

    static Opt<VertexShader> CompileVertexShader(const String& source);
    static Opt<FragmentShader> CompileFragmentShader(const String& source);
    static Opt<GeometryShader> CompileGeometryShader(const String& source);
    static Opt<TessEvaluationShader> CompileTessEvaluationShader(const String& source);
    static Opt<TessControlShader> CompileTessControlShader(const String& source);
    static Opt<ComputeShader> CompileComputeShader(const String& source);
protected:
    void Init();
};

class RenderShader : public Shader {
protected:
    RenderShader() : Shader() {}
};

class VertexShader : public RenderShader {
public:
    VertexShader() : RenderShader() {}
    inline ShaderType GetType() override { return ShaderType::VERTEX; }
};
class FragmentShader : public RenderShader {
public:
    FragmentShader() : RenderShader() {}
    inline ShaderType GetType() override { return ShaderType::FRAGMENT; }
};
class GeometryShader : public RenderShader {
public:
    GeometryShader() : RenderShader() {}
    inline ShaderType GetType() override { return ShaderType::GEOMETRY; }
};
class TessEvaluationShader : public RenderShader {
public:
    TessEvaluationShader() : RenderShader() {}
    inline ShaderType GetType() override { return ShaderType::TESS_EVALUATION; }
};
class TessControlShader : public RenderShader {
public:
    TessControlShader() : RenderShader() {}
    inline ShaderType GetType() override { return ShaderType::TESS_CONTROL; }
};

class ComputeShader : public Shader {
public:
    ComputeShader() : Shader() {}
    inline ShaderType GetType() override { return ShaderType::COMPUTE; }
};

}

#endif // PGR_SHADER_HPP