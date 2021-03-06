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
#include "Camera.hpp"

namespace sadekpet {

/**
 * @brief Slouží určení pořadí vykteslování objektů. Jedna vrstva má svůj vlasní strom nodů.
 */
class Layer
{
private:
    String m_name;
    size_t m_number;
    UnordMap<uint, Node*> m_roots;
    UnordMap<uint, VisibleNode*> m_visible;
    Camera* m_curretCamera;
    bool m_clearDepth;
    bool m_writeDepth;
public:
    Layer(String name, size_t number) : m_name(name), m_number(number), m_curretCamera(nullptr), m_clearDepth(true), m_writeDepth(true) {}
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
    void SetCurrentCamera(Camera* camera) { m_curretCamera = camera; }
    Camera* GetCurrentCamera() const { return m_curretCamera; }
    UnordMap<uint, Node*>& Roots() { return m_roots; }
    UnordMap<uint, VisibleNode*>& Visible() { return m_visible; }
    bool& DoClearDepth() { return m_clearDepth; }
    bool& DoWriteDepth() { return m_writeDepth; }
};

/**
 * @brief Slouží určení pořadí vykteslování objektů, podle pořadí vrstev. Např vrstvy: skybox, 3D scéna, 2D UI.
 */
class Layers
{
private:
    static Vector<Layer*> s_layers;
    static Layer* s_current;
public:
    static int Add(String name) {
        size_t number = Count();
        s_layers.push_back(new Layer(name, number));
        return number;
    }
    static Layer* Get(size_t number) { return s_layers[number]; }
    static size_t Count() { return s_layers.size(); }
    static Layer* GetCurrent() { return s_current; } 
    static void SetCurrent(Layer* layer) { s_current = layer; }
};

}

#endif // PGR_LAYERS_HPP