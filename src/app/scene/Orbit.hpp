/**
 * @file Orbit.hpp
 * @author sadekpet
 * @brief 
 * @date 2020-03-21
 * 
 */

#ifndef PGR_ORBIT_HPP
#define PGR_ORBIT_HPP

#include <core/scene/Node.hpp>
#include "SpaceBody.hpp"
#include "ShaderContexts.hpp"

namespace sadekpet {

/**
 * @brief Umožňuje rotaci kolem počátku v lokálním souřadnicovém systému. Dá se vizualizovat kruhem (v základu vypnuto).
 */
class Orbit : public VisibleNode
{
private:
    SpaceBody* m_body;
    float m_radius;
    float m_speed;
    float m_phi;
    Line3DShaderContext m_shaderContext;
    Shared<Line3DShaderContextUpdater> m_shaderContextUpdater;
    bool m_move = true;
public:
    Orbit(SpaceBody* body, float radius = 1, float speed = 1, float start = 0);

    SpaceBody* GetBody() { return m_body; }
    void Update(float deltaTime) override;
    void Move(float phi);
    bool& IsMoving() { return m_move; }
    ShaderContext& GetShaderContext() override { return m_shaderContext; }
    float GetPhi() const { return m_phi; }
    void SetPhi(float phi) { m_phi = phi; }
};

}

#endif // PGR_ORBIT_HPP