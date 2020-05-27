#include "Uniforms.hpp"

#include "OpenGL.hpp"
#include <core/scene/Node.hpp>
#include <core/scene/Layers.hpp>

#include <iostream>

namespace sadekpet {


int IUniform::GetLocation(int programID)
{
    if(m_loc == -1) {
        m_loc = GL(GetUniformLocation(programID, m_name.c_str()));
    }
    return m_loc;
}
void IUniform::Set(int loc, int v)
{
    GL(Uniform1i(loc, v));
}
void IUniform::Set(int loc, float v)
{
    GL(Uniform1f(loc, v));
}
void IUniform::Set(int loc, glm::vec2 v)
{
    GL(Uniform2f(loc, v.x, v.y));
}
void IUniform::Set(int loc, glm::vec3 v)
{
    GL(Uniform3f(loc, v.x, v.y, v.z));
}
void IUniform::Set(int loc, glm::vec4 v)
{
    GL(Uniform4f(loc, v.x, v.y, v.z, v.w));
}
void IUniform::Set(int loc, glm::mat2 v)
{
    GL(UniformMatrix2fv(loc, 1, false, &v[0][0]));
}
void IUniform::Set(int loc, glm::mat3 v)
{
    GL(UniformMatrix3fv(loc, 1, false, &v[0][0]));
}
void IUniform::Set(int loc, glm::mat4 v)
{
    GL(UniformMatrix4fv(loc, 1, false, &v[0][0]));
}

void Uniforms::SetUniforms(int programID)
{
    for(const Unique<IUniform>& uniform : m_uniforms) {
        uniform->Set(programID);
    }
}
void Uniforms::AddUniform(IUniform* uniform)
{
    m_uniforms.push_back(Unique<IUniform>(uniform));
}

Uniforms::Uniforms(const glm::mat4& M, const glm::mat4& V, const glm::mat4& P)
{
    m_M = new Uniform<glm::mat4>("M",M);
    m_V = new Uniform<glm::mat4>("V",V);
    m_P = new Uniform<glm::mat4>("P",P);
    m_VM = new Uniform<glm::mat4>("VM",V*m_M->value);
    m_PVM = new Uniform<glm::mat4>("PVM",P*m_VM->value);
    m_N = new Uniform<glm::mat3>("N", GetN(M));
    AddUniform(m_M);
    AddUniform(m_V);
    AddUniform(m_P);
    AddUniform(m_VM);
    AddUniform(m_PVM);
    AddUniform(m_N);
}

void Uniforms::UpdateMVP(const glm::mat4& M, const glm::mat4& V, const glm::mat4& P)
{
    m_M->value = M;
    m_V->value = V;
    m_P->value = P;
    m_VM->value = V*M;
    m_PVM->value = P*m_VM->value;
    m_N->value = GetN(M);
}

glm::mat3 Uniforms::GetN(const glm::mat4& M)
{
    glm::mat3 N = glm::mat3(M);
    return glm::transpose(glm::inverse(N));
}

}