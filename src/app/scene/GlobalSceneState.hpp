/**
 * @file GlobalSceneState.hpp
 * @author sadekpet (sadekpet@fel.cvut.cz)
 * @brief 
 * @date 2020-05-29
 */

#ifndef PGR_GLOBAL_SCENE_STATE_HPP
#define PGR_GLOBAL_SCENE_STATE_HPP

#include <core/render/Light.hpp>
#include <core/scene/ParticleSystem.hpp>

namespace sadekpet {

/**
 * @brief Globální stav scény pro shadery. Obsahuje stav světel a fogu.
 */
class GlobalSceneState
{
public:
    static Light dirLight;
    static Light pointLight;
    static Light spotLight;
    static float fog;
    static Unique<ParticleSystem> smokeParticleSystem;
};

}

#endif // PGR_GLOBAL_SCENE_STATE_HPP