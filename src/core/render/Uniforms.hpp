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

class IUniform
{
private:
    int m_loc;
    String m_name;
public:
    IUniform(String name) : m_loc(-1), m_name(name) {}
    virtual void Set(int programID) = 0;
    const String& GetName() const { return m_name; }
protected:
    int GetLocation(int programID);
    void Set(int loc, int v);
    void Set(int loc, float v);
    void Set(int loc, glm::vec2 v);
    void Set(int loc, glm::vec3 v);
    void Set(int loc, glm::vec4 v);
    void Set(int loc, glm::mat2 v);
    void Set(int loc, glm::mat3 v);
    void Set(int loc, glm::mat4 v);
};

template<typename T>
class Uniform : public IUniform
{
public:
    T value;
    Uniform(String name, const T& v) : IUniform(name), value(v) {}
    void Set(int programID) override {
        IUniform::Set(GetLocation(programID), value);
    }
};

class Uniforms
{
private:
    Vector<Unique<IUniform>> m_uniforms;
    Uniform<glm::mat4>* m_M;
    Uniform<glm::mat4>* m_VM;
    Uniform<glm::mat4>* m_PVM;
public:
    Uniforms() : Uniforms(glm::mat4(1), glm::mat4(1), glm::mat4(1)) {}
    Uniforms(const glm::mat4& M, const glm::mat4& V, const glm::mat4& P);
    void UpdateMVP(const glm::mat4& M, const glm::mat4& V, const glm::mat4& P);
    void SetUniforms(int programID);
protected:
    void AddUniform(IUniform* uniform);
};

}

#endif // PGR_UNIFORMS_HPP