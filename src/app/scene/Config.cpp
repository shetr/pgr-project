#include "Config.hpp"

#include <iostream>

#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <iomanip>
#include <tuple>
#include <algorithm>
#include <sstream>

#include <core/Console.hpp>

namespace sadekpet {

Config::Config(UnordMap<String, Orbit*> orbits)
    : m_orbits(orbits), m_filePath("res/config.txt")
{
}

void Config::Load()
{
    std::ifstream ifs(m_filePath);
    if(!ifs) {
        std::cout << "Cannot open config file" << std::endl;
        return;
    }
    Material mat;
    String line;
    while(std::getline(ifs, line)){
        size_t spacePos = line.find(" ");
        if (spacePos != std::string::npos) {
            String objName = line.substr(0, spacePos);
            String lineValues = line.substr(spacePos + 1);
            std::stringstream ss(lineValues);
            auto it = m_orbits.find(objName);
            if(it != m_orbits.end()) {
                float phi = 0;
                ss >> phi;
                it->second->SetPhi(glm::radians(phi));
            }
        }

    }
}

}