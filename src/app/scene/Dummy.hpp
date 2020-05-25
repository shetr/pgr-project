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

class Dummy : public VisibleNode
{
private:
    Object3DShaderContext m_shaderContext;
    Shared<Object3DShaderContextUpdater> m_shaderContextUpdater;
public:
    Dummy(const String& model, const String& texture) : m_shaderContext(model, texture) {
        m_shaderContextUpdater = Shared<Object3DShaderContextUpdater>(new Object3DShaderContextUpdater(&m_shaderContext));
        AddShaderContextUpdater(m_shaderContextUpdater);
    }
    ShaderContext& GetShaderContext() override { return m_shaderContext; }
};

}

#endif // PGR_DUMMY_HPP