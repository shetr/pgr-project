/**
 * @file Layers.hpp
 * @author sadekpet
 * @brief 
 * @date 2020-02-26
 * 
 */

#ifndef PGR_LAYERS_HPP
#define PGR_LAYERS_HPP

#include <core/types.hpp>
#include "Node.hpp"

namespace sadekpet {

class Layer
{
private:
    String m_name;
    size_t m_number;
    UnordMap<uint, Node*> m_roots;
    UnordMap<uint, VisibleNode*> m_visible;
public:
    Layer(String name, size_t number) : m_name(name), m_number(number) {}
    const String& GetName() { return m_name; }
    size_t GetNumber() { return m_number; }
    void Add(VisibleNode* node) { 
        m_visible[node->GetID()] = node;
        Add((Node*)node);
    }
    void Add(Node* node) { 
        m_roots[node->GetID()] = node;
        node->SetLayer(this);
    }
    UnordMap<uint, Node*>& Roots() { return m_roots; }
    UnordMap<uint, VisibleNode*>& Visible() { return m_visible; }
};

class Layers
{
private:
    static Vector<Layer> s_layers;
    static UnordMap<String, size_t> s_namesToLayer;
public:
    static int Add(String name) {
        size_t number = Count();
        s_namesToLayer[name] = number;
        s_layers.push_back(Layer(name, number));
        return number;
    }
    static Layer& Get(size_t number) { return s_layers[number]; }
    static Layer& Get(String name) { return s_layers[s_namesToLayer[name]]; }
    static size_t Count() { return s_layers.size(); }
};

}

#endif // PGR_LAYERS_HPP