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

struct Light
{
    int type = 0;
    glm::vec4 position = glm::vec4(0.0, 0.0, 1.0, 0.0);
    glm::vec3 ambient = glm::vec3(0.0, 0.0, 0.0);
    glm::vec3 diffuse = glm::vec3(1.0, 1.0, 1.0);
    glm::vec3 specular = glm::vec3(1.0, 1.0, 1.0);
    glm::vec3 spotDir = glm::vec3(0.0, 0.0, -1.0);
    float spotExponent = 0;
    float spotCutoff = M_PI;
    float attenuation = 1;
};

}

#endif // PGR_LIGHT_HPP