#ifndef PGR_GRAPHICS_PROGRAM_HPP
#define PGR_GRAPHICS_PROGRAM_HPP

#include <core/types.hpp>
#include "Shader.hpp"

namespace sadekpet
{

class GraphicsProgramLinker;
class ComputeProgramLinker;
class RenderProgramLinker;

class GraphicsProgram
{
    friend class GraphicsProgramLinker;
    friend class ComputeProgramLinker;
    friend class RenderProgramLinker;
private:
    uint m_id;
public:
    GraphicsProgram(GraphicsProgram&& old);
    ~GraphicsProgram();
    GraphicsProgram& operator=(GraphicsProgram&& old);
    uint GetID() const { return m_id; }
    void Bind() const;
    static void UnBind();
private:
    GraphicsProgram(uint id) : m_id(id) {}
};

class GraphicsProgramLinker
{
protected:
    Vector<Shader const*> m_shaders;
public:
    GraphicsProgramLinker();
    Opt<GraphicsProgram*> Link();
};

class RenderProgramLinker : public GraphicsProgramLinker
{
public:
    RenderProgramLinker() : GraphicsProgramLinker() {}
    void AddShader(const RenderShader& shader);
};

class ComputeProgramLinker : public GraphicsProgramLinker
{
public:
    ComputeProgramLinker() : GraphicsProgramLinker() {}
    void AddShader(const ComputeShader& shader);
};

}

#endif // PGR_GRAPHICS_PROGRAM_HPP