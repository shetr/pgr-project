/**
 * @file Node.hpp
 * @author sadekpet
 * @brief 
 * @date 2020-02-26
 */

#ifndef PGR_NODE_HPP
#define PGR_NODE_HPP

#include <core/types.hpp>
#include <core/render/ShaderContext.hpp>
#include <glm/glm.hpp>

#include "TimeGroup.hpp"

namespace sadekpet {

class Layer;

/**
 * @brief Reprezentuje lokální transformaci objektu, tedy jeho pozici, rotaci a velikost.
 */
struct Transform
{
    glm::vec3 pos;
    glm::vec3 scale;
    float rotAngle;
    glm::vec3 rotAxis;

    Transform() : pos(0.0f), scale(1.0f), rotAngle(0.0f), rotAxis(glm::vec3(0,0,1)) {}

    glm::mat4 ToMat4() const;
    glm::mat4 ToMat4NoScale() const;
};

/**
 * @brief Slouží jako uzel ve stromovém grafu scény. Každý má svojí lokální transformaci vůči svému rodiči.
 */
class Node
{
public:
    using Iterator = UnordMap<uint, Node*>::iterator;
private:
    static uint s_idGen;
    static UnordMap<uint, Node*> s_nodesMap;
    static Shared<TimeGroup> s_globalTimeGroup;
    uint m_id;
    Node* m_parent;
    UnordMap<uint, Node*> m_childsMap;
    Layer* m_layer;
protected:
    Transform m_transform;
    glm::mat4 m_worldTransform;
    glm::mat4 m_worldTransformScaled;
    Shared<TimeGroup> m_timeGroup;
public:
    Node();
    virtual ~Node();

    static Node* GetNode(uint id);

    void SetLayer(Layer* layer) { m_layer = layer; }
    void SetTimeGroup(const Shared<TimeGroup>& timeGroup) { m_timeGroup = timeGroup; }

    uint GetID() const { return m_id; }
    Node* GetParent() const { return m_parent; }
    Transform& GetTransform() { return m_transform; }
    const glm::mat4& GetWorldTransform() const { return m_worldTransformScaled; }
    glm::vec3 GetWorldPos() const { return m_worldTransformScaled[3]; }
    Layer* GetLayer() { return m_layer; }
    float GetTimeSpeed() const { return m_timeGroup->Speed(); }
    Iterator ChildsBegin() { return m_childsMap.begin(); }
    Iterator ChildsEnd() { return m_childsMap.end(); }

    void ConnectChild(Node* child);

    void SetRoot();

    void UpdateWorldTransform();

    virtual void Update(float deltaTime) {}
    virtual uint8_t GetStencilID() const { return 0; }

protected:
    void DisconnectChild(Node* child);
};

/**
 * @brief Pro automatický update dat shaderu.
 */
class ShaderContextUpdater
{
public:
    virtual void Update() = 0;
};

/**
 * @brief Uzel grafu scény který může být vykreslen - obsahuje ShaderContext.
 */
class VisibleNode : public Node
{
private:
    bool m_isVisible;
    Vector<Shared<ShaderContextUpdater>> m_shaderContextUpdaters;
public:
    VisibleNode() : m_isVisible(true){}
    virtual ~VisibleNode();
    virtual ShaderContext& GetShaderContext() = 0;
    void UpdateShaderContext();
    void AddShaderContextUpdater(const Shared<ShaderContextUpdater>& updater);
    bool IsVisible() const { return m_isVisible; }
    bool& IsVisible() { return m_isVisible; }
    void Show() { m_isVisible = true; }
    void Hide() { m_isVisible = false; }
};

}

#endif // PGR_NODE_HPP