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

#include "Light.hpp"

namespace sadekpet {

class Node;

class IUniform
{
public:
    virtual void Set(int programID) = 0;
};

class IUniformSingle : public IUniform
{
private:
    int m_loc;
    String m_name;
public:
    IUniformSingle(String name) : m_loc(-1), m_name(name) {}
    virtual void Set(int programID) = 0;
    const String& GetName() const { return m_name; }
protected:
    int GetLocation(int programID);
    void Set(int loc, int v);
    void Set(int loc, glm::ivec2 v);
    void Set(int loc, glm::ivec3 v);
    void Set(int loc, glm::ivec4 v);
    void Set(int loc, bool v);
    void Set(int loc, LightType v);
    void Set(int loc, float v);
    void Set(int loc, glm::vec2 v);
    void Set(int loc, glm::vec3 v);
    void Set(int loc, glm::vec4 v);
    void Set(int loc, glm::mat2 v);
    void Set(int loc, glm::mat3 v);
    void Set(int loc, glm::mat4 v);
    void Set(int loc, Vector<float>& v);
};

template<typename T>
class Uniform : public IUniformSingle
{
public:
    T value;
    Uniform(String name, const T& v) : IUniformSingle(name), value(v) {}
    void Set(int programID) override {
        IUniformSingle::Set(GetLocation(programID), value);
    }
};

template<typename T>
class UniformArray : public IUniform
{
private:
    Unique<Uniform<int>> m_size;
    Unique<Uniform<Vector<T>>> m_array;
public:
    UniformArray(const String& name, const Vector<T>& values) {
        m_size = Unique<Uniform<int>>(new Uniform<int>(name+"_size", values.size()));
        m_array = Unique<Uniform<Vector<T>>>(new Uniform<Vector<T>>(name, values));
    }
    void Set(int programID) override {
        m_size->Set(programID);
        m_array->Set(programID);
    }
    void Update(const Vector<T>& values) {
        m_size->value = values.size();
        m_array->value = values;
    }
};

class UniformStruct : public IUniform
{
private:
    Vector<Unique<IUniformSingle>> m_uniforms;
    String m_StructName;
public:
    UniformStruct(const String& structName);
    void Set(int programID) override;
protected:
    template<typename T>
    inline Uniform<T>* AddUniform(const String& name, const T value) {
        Uniform<T>* u = new Uniform<T>(m_StructName+"."+name, value);
        m_uniforms.push_back(Unique<IUniformSingle>(u));
        return u;
    }
};

class Uniforms
{
private:
    Vector<Unique<IUniform>> m_uniforms;
    Uniform<glm::mat4>* m_M;
    Uniform<glm::mat4>* m_V;
    Uniform<glm::mat4>* m_P;
    Uniform<glm::mat4>* m_VM;
    Uniform<glm::mat4>* m_PVM;
    Uniform<glm::mat3>* m_N;
public:
    Uniforms() : Uniforms(glm::mat4(1), glm::mat4(1), glm::mat4(1)) {}
    Uniforms(const glm::mat4& M, const glm::mat4& V, const glm::mat4& P);
    void UpdateMVP(const glm::mat4& M, const glm::mat4& V, const glm::mat4& P);
    void SetUniforms(int programID);
protected:
    void AddUniform(IUniform* uniform);
private:
    glm::mat3 GetN(const glm::mat4& M);
};

}

#endif // PGR_UNIFORMS_HPP