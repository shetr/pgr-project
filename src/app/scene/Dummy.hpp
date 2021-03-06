/**
 * @file Dummy.hpp
 * @author sadekpet
 * @brief 
 * @date 2020-05-25
 * 
 */

#ifndef PGR_DUMMY_HPP
#define PGR_DUMMY_HPP

#include <core/scene/Node.hpp>
#include "ShaderContexts.hpp"

namespace sadekpet {

/**
 * @brief Slouží k jednoduchém vložení modelu do scény, který sám o sobě nic nedělá.
 */
class Dummy : public VisibleNode
{
private:
    Object3DShaderContext m_shaderContext;
    Shared<Object3DShaderContextUpdater> m_shaderContextUpdater;
public:
    Dummy(const String& model, const String& texture)
        : Dummy(model, texture, Material()) {}
    Dummy(const String& model, const String& texture, const Material material) : m_shaderContext(model, texture, material) {
        m_shaderContextUpdater = Shared<Object3DShaderContextUpdater>(new Object3DShaderContextUpdater(&m_shaderContext));
        AddShaderContextUpdater(m_shaderContextUpdater);
    }
    ShaderContext& GetShaderContext() override { return m_shaderContext; }
    Object3DShaderContext& GetObject3DShaderContext() { return m_shaderContext; }
    Shared<Object3DShaderContextUpdater> GetShaderContextUdater() { return m_shaderContextUpdater; }
};

}

#endif // PGR_DUMMY_HPP