/**
 * @file Material.hpp
 * @author sadekpet (sadekpet@fel.cvut.cz)
 * @brief 
 * @date 2020-05-29
 */

#ifndef PGR_MATERIAL_HPP
#define PGR_MATERIAL_HPP

#include <glm/glm.hpp>

namespace sadekpet {

/**
 * @brief Struktura pro ukládání vlastností materiálu.
 */
struct Material
{
    glm::vec3 ambient = glm::vec3(0.1,0.1,0.1);
    glm::vec3 diffuse = glm::vec3(0.8,0.8,0.8);
    glm::vec3 specular = glm::vec3(1.0,1.0,1.0);
    glm::vec3 emission = glm::vec3(0.0,0.0,0.0);
    float shinines = 1;
};

}

#endif // PGR_MATERIAL_HPP