#include "Uniforms.hpp"

#include "OpenGL.hpp"
#include <core/scene/Node.hpp>
#include <core/scene/Camera.hpp>

#include <iostream>

template<typename T>
int sadekpet::Uniform<T>::GetLocation(int programID)
{
    if(m_loc == -1) {
        m_loc = GL(GetUniformLocation(programID, name.c_str()));
    }
    return m_loc;
}

namespace sadekpet {


void Uniforms::SetMVP(const glm::mat4& M, const glm::mat4& V, const glm::mat4& P)
{
    m_M.value = M;
    m_VM.value = V*M;
    m_PVM.value = P*m_VM.value;
}
void Uniforms::SetUniforms(int programID)
{
    Set(programID, m_M);
    Set(programID, m_VM);
    Set(programID, m_PVM);
    SetUniformsImpl(programID);
}

void Uniforms::Update()
{
    Camera* camera = Camera::GetCurrent();
    SetMVP(m_owner->GetWorldTransform(), glm::inverse(camera->GetWorldTransform()), camera->GetProjection());
    UpdateImpl();
}

void Uniforms::Set(int programID, Uniform<float>& u)
{
    GL(Uniform1f(u.GetLocation(programID), u.value));
}
void Uniforms::Set(int programID, Uniform<glm::vec2>& u)
{
    GL(Uniform2f(u.GetLocation(programID), u.value.x, u.value.y));
}
void Uniforms::Set(int programID, Uniform<glm::vec3>& u)
{
    GL(Uniform3f(u.GetLocation(programID), u.value.x, u.value.y, u.value.z));
}
void Uniforms::Set(int programID, Uniform<glm::vec4>& u)
{
    GL(Uniform4f(u.GetLocation(programID), u.value.x, u.value.y, u.value.z, u.value.w));
}
void Uniforms::Set(int programID, Uniform<glm::mat2>& u)
{
    GL(UniformMatrix2fv(u.GetLocation(programID), 1, false, &u.value[0][0]));
}
void Uniforms::Set(int programID, Uniform<glm::mat3>& u)
{
    GL(UniformMatrix3fv(u.GetLocation(programID), 1, false, &u.value[0][0]));
}
void Uniforms::Set(int programID, Uniform<glm::mat4>& u)
{
    GL(UniformMatrix4fv(u.GetLocation(programID), 1, false, &u.value[0][0]));
}

}