#include "GlobalSceneState.hpp"

namespace sadekpet {

Light GlobalSceneState::dirLight;
Light GlobalSceneState::pointLight;
Light GlobalSceneState::spotLight;
float GlobalSceneState::fog = 0.001;
Unique<ParticleSystem> GlobalSceneState::smokeParticleSystem;

}