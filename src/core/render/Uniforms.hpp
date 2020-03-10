/**
 * @file Uniforms.hpp
 * @author sadekpet ()
 * @brief
 * 
 */

#ifndef PGR_UNIFORMS_HPP
#define PGR_UNIFORMS_HPP

#include <core/types.hpp>
#include <glm/glm.hpp>

namespace sadekpet {

class Node;

template<typename T>
class Uniform
{
private:
    int m_loc;
public:
    String name;
    T value;
    Uniform(String n, const T& v) : m_loc(-1), name(n), value(v) {}
    int GetLocation(int programID);
};

class Uniforms
{
protected:
    Node* m_owner;
private:
    Uniform<glm::mat4> m_M;
    Uniform<glm::mat4> m_VM;
    Uniform<glm::mat4> m_PVM;
public: 
    Uniforms() : Uniforms(glm::mat4(1), glm::mat4(1), glm::mat4(1)) {}
    Uniforms(const glm::mat4& M, const glm::mat4& V, const glm::mat4& P) 
        : m_M("M",M), m_VM("VM",V*m_M.value), m_PVM("PVM",P*m_VM.value) {}
    void SetOwner(Node* owner) { m_owner = owner; }
    void SetUniforms(int programID);
    void Update();
protected:
    virtual void SetUniformsImpl(int programID) {};
    virtual void UpdateImpl() {};
    void Set(int programID, Uniform<float>& u);
    void Set(int programID, Uniform<glm::vec2>& u);
    void Set(int programID, Uniform<glm::vec3>& u);
    void Set(int programID, Uniform<glm::vec4>& u);
    void Set(int programID, Uniform<glm::mat2>& u);
    void Set(int programID, Uniform<glm::mat3>& u);
    void Set(int programID, Uniform<glm::mat4>& u);
private:
    void SetMVP(const glm::mat4& M, const glm::mat4& V, const glm::mat4& P);
};

}

#endif // PGR_UNIFORMS_HPP