/**
 * @file Console.hpp
 * @author sadekpet (sadekpet@fel.cvut.cz)
 * @brief 
 * @date 2020-05-28
 */

#ifndef PGR_CONSOLE_HPP
#define PGR_CONSOLE_HPP

#include <core/render/OpenGL.hpp>
#include <iostream>

namespace sadekpet {



}

std::ostream& operator<<(std::ostream& os, const glm::vec2& v);

std::ostream& operator<<(std::ostream& os, const glm::vec3& v);

std::ostream& operator<<(std::ostream& os, const glm::vec4& v);

#endif // PGR_CONSOLE_HPP