#include "ShaderContext.hpp"

#include "OpenGL.hpp"

namespace sadekpet {

void ShaderContext::DrawFunction()
{
    GL(DrawElements(static_cast<uint>(GetPrimitives()->GetType()), GetPrimitives()->GetCount(), GL_UNSIGNED_INT, 0));
}


void InstancedShaderContext::DrawFunction()
{
    BeforeDraw();
    GL(DrawArraysInstanced(static_cast<uint>(GetPrimitives()->GetType()), GetStartIndex(), GetVertexCount(), GetInstanceCount()));
}

}