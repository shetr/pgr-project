#include "PrimitivesManager.hpp"

#include <iostream>

#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <iomanip>

namespace sadekpet {

PrimitivesManager* PrimitivesManager::s_instance = nullptr;
String PrimitivesManager::s_modelsPath = "res/models/";

PrimitivesManager* PrimitivesManager::Init()
{
    if(s_instance == nullptr) {
        s_instance = new PrimitivesManager();
    }
    return s_instance;
}
PrimitivesManager::~PrimitivesManager()
{
    s_instance = nullptr;
}

void PrimitivesManager::AddPrimitives(const String& name, Primitives* primitives)
{
    s_instance->m_primitives.insert({name, Shared<Primitives>(primitives)});
}

Shared<Primitives> PrimitivesManager::GetPrimitives(const String& name)
{
    UnordMap<String, Shared<Primitives>>::iterator it = s_instance->m_primitives.find(name);
    return it->second;
}

void PrimitivesManager::LoadModel(const String& name)
{
    String path = s_modelsPath+name+".obj";
    std::ifstream ifs(path);
    if(!ifs) {
        std::cout << "Cannot open model file" << std::endl;
        return;
    }
    Vector<glm::vec3> vertices;
    Vector<glm::vec3> normals;
    Vector<glm::vec2> uvs;
    Vector<int> indices;

    String line;
    while(std::getline(ifs, line)){
        size_t spacePos = line.find(" ");
        if (spacePos != std::string::npos) {
            String lineType = line.substr(0, spacePos);
            String lineValues = line.substr(spacePos + 1);
            //std::cout << lineType << " ";
            std::stringstream ss(lineValues);
            if(lineType == "v") {
                glm::vec3 v;
                ss >> v.x;
                ss >> v.y;
                ss >> v.z;
                //std::cout << v.x << " " << v.y << " " << v.z << std::endl;
                vertices.push_back(v);
            } else if(lineType == "vn") {
                glm::vec3 n;
                ss >> n.x;
                ss >> n.y;
                ss >> n.z;
                //std::cout << n.x << " " << n.y << " " << n.z << std::endl;
                normals.push_back(n);
            } else if(lineType == "vt") {
                glm::vec2 uv;
                ss >> uv.x;
                ss >> uv.y;
                //std::cout << uv.x << " " << uv.y << std::endl;
                uvs.push_back(uv);
            } else if(lineType == "f") {
                String lineTriangle;
                while(std::getline(ss, lineTriangle, ' ')) {
                    std::stringstream triss(lineTriangle);
                    String lineTrianglePoint;
                    if(lineTriangle.size() > 1) {
                        while(std::getline(triss, lineTrianglePoint, '/')) {
                            if(!lineTrianglePoint.empty()) {
                                std::stringstream vss(lineTrianglePoint);
                                int i;
                                vss >> i;
                                //std::cout << i << "/";
                                indices.push_back(i - 1);
                            }
                        }
                    }
                    //std::cout << " ";
                }
                //std::cout << std::endl;
            }
        }

    }

    Mesh3D* mesh = new Mesh3D(vertices.size(), indices.size(), vertices.data(), uvs.data(), normals.data(), indices.data());
    AddPrimitives(name, mesh);
}

PrimitivesManager::PrimitivesManager()
{
}

}