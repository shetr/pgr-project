/**
 * @file Light.hpp
 * @author sadekpet (sadekpet@fel.cvut.cz)
 * @brief 
 * @date 2020-05-29
 */

#ifndef PGR_LIGHT_HPP
#define PGR_LIGHT_HPP

#include <core/types.hpp>
#include <glm/glm.hpp>

namespace sadekpet {

enum class LightType : int
{
    NONE = 0,
    DIR = 1,
    POINT = 2,
    SPOT = 3
};

struct Light
{
    LightType lightType = LightType::NONE;
    glm::vec4 position = glm::vec4(0.0, 0.0, 1.0, 0.0);
    glm::vec3 ambient = glm::vec3(0.0, 0.0, 0.0);
    glm::vec3 diffuse = glm::vec3(1.0, 1.0, 1.0);
    glm::vec3 specular = glm::vec3(1.0, 1.0, 1.0);
    glm::vec3 spotDir = glm::vec3(0.0, 0.0, -1.0);
    float spotExponent = 1;
    float spotCutoff = M_PI;
    float attenuationConst = 0;
    float attenuationLin = 1;
};

}

#endif // PGR_LIGHT_HPP