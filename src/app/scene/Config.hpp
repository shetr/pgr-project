/**
 * @file Config.hpp
 * @author sadekpet (sadekpet@fel.cvut.cz)
 * @brief
 * @date 2020-06-01
 */

#ifndef PGR_CONFIG_HPP
#define PGR_CONFIG_HPP

#include "Orbit.hpp"

namespace sadekpet {

class Config
{
private:
    UnordMap<String, Orbit*> m_orbits;
    String m_filePath;
public:
    Config(UnordMap<String, Orbit*> orbits);

    void Load();
};

}

#endif // PGR_CONFIG_HPP