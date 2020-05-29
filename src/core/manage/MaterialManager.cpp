#include "MaterialManager.hpp"

#include <iostream>

#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <iomanip>
#include <tuple>
#include <algorithm>

#include <core/Console.hpp>

namespace sadekpet {

MaterialManager* MaterialManager::s_instance = nullptr;
String MaterialManager::s_materialsPath = "res/materials/";

MaterialManager* MaterialManager::Init()
{
    if(s_instance == nullptr) {
        s_instance = new MaterialManager();
    }
    return s_instance;
}
MaterialManager::~MaterialManager()
{
    s_instance = nullptr;
}

void MaterialManager::AddMaterial(const String& name, const Material& material)
{
    s_instance->m_materials.insert({name, material});
}

Material MaterialManager::GetMaterial(const String& name)
{
    UnordMap<String, Material>::iterator it = s_instance->m_materials.find(name);
    return it->second;
}


void MaterialManager::LoadMaterial(const String& name)
{
    String path = s_materialsPath+name+".mtl";
    std::ifstream ifs(path);
    if(!ifs) {
        std::cout << "Cannot open material file" << std::endl;
        return;
    }
    Material mat;
    String line;
    while(std::getline(ifs, line)){
        size_t spacePos = line.find(" ");
        if (spacePos != std::string::npos) {
            String lineType = line.substr(0, spacePos);
            String lineValues = line.substr(spacePos + 1);
            std::stringstream ss(lineValues);
            if(lineType == "\tKa") {
                glm::vec3 v;
                ss >> v.x;
                ss >> v.y;
                ss >> v.z;
                std::cout << v.x << " " << v.y << " " << v.z << std::endl;
                mat.ambient = v;
            } else if(lineType == "\tKd") {
                glm::vec3 v;
                ss >> v.x;
                ss >> v.y;
                ss >> v.z;
                std::cout << v.x << " " << v.y << " " << v.z << std::endl;
                mat.difuse = v;
            } else if(lineType == "\tKs") {
                glm::vec3 v;
                ss >> v.x;
                ss >> v.y;
                ss >> v.z;
                std::cout << v.x << " " << v.y << " " << v.z << std::endl;
                mat.specular = v;
            } else if(lineType == "\tKe") {
                glm::vec3 v;
                ss >> v.x;
                ss >> v.y;
                ss >> v.z;
                std::cout << v.x << " " << v.y << " " << v.z << std::endl;
                mat.emission = v;
            }
        }

    }

    AddMaterial(name, mat);
}

MaterialManager::MaterialManager()
{
}

}