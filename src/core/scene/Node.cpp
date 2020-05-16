#include "Node.hpp"

#include <glm/gtx/transform.hpp>

#include <iostream>

#include "Layers.hpp"
#include "Camera.hpp"

namespace sadekpet {

glm::mat4 Transform::ToMat4() const
{
    return glm::translate(pos) * glm::rotate(rotAngle, rotAxis) * glm::scale(scale);
}

uint Node::s_idGen = 0;
UnordMap<uint, Node*> Node::s_nodesMap = {};

Node::Node() : m_id(s_idGen++), m_layer(nullptr), m_parent(nullptr), m_worldTransform(glm::mat4(1))
{
    s_nodesMap[m_id] = this;
}

Node::~Node()
{
    if(m_parent != nullptr) {
        m_parent->DisconnectChild(this);
    } /*else {
        m_layer->Roots().erase(GetID());
    }*/
    s_nodesMap.erase(GetID());
    for(Pair<uint, Node*> pair : m_childsMap) {
        delete pair.second;
    }
}

Node* Node::GetNode(uint id)
{
    return s_nodesMap[id];
}

void Node::ConnectChild(Node* child)
{
    if(child->m_parent != nullptr) {
        child->m_parent->DisconnectChild(child);
    } /*else {
        m_layer->Roots().erase(child->GetID());
    }*/
    m_childsMap[child->GetID()] = child;
    child->m_parent = this;
}

void Node::DisconnectChild(Node* child)
{
    m_childsMap.erase(child->GetID());
    child->m_parent = nullptr;
}

void Node::SetRoot()
{
    if(m_parent != nullptr) {
        m_parent->DisconnectChild(this);
    }
    m_parent = nullptr;
    m_layer->Roots()[GetID()] = this;
}

void Node::UpdateWorldTransform()
{
    glm::mat4 parentTransform = (m_parent == nullptr) ? glm::mat4(1.0f) : m_parent->m_worldTransform;
    m_worldTransform = parentTransform * m_transform.ToMat4();
    for(Pair<uint, Node*> p : m_childsMap) {
        p.second->UpdateWorldTransform();
    }
}

VisibleNode::~VisibleNode()
{
    GetLayer()->Visible().erase(GetID());
}

void VisibleNode::UpdateShaderContext()
{
    Layer* layer = Layers::GetCurrent();
    if(layer != nullptr) {
        Camera* camera = layer->GetCurrentCamera();
        if(camera != nullptr) { 
            GetShaderContext().GetUniforms().UpdateMVP(GetWorldTransform(), glm::inverse(camera->GetWorldTransform()), camera->GetProjection());
        }
    }
    for(Shared<ShaderContextUpdater>& updater : m_shaderContextUpdaters) {
        updater->Update();
    }
}


void VisibleNode::AddShaderContextUpdater(const Shared<ShaderContextUpdater>& updater)
{
    m_shaderContextUpdaters.push_back(updater);
}

}