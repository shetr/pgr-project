#include "PrimitivesManager.hpp"

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
    Vector<glm::vec3> inVertices;
    Vector<glm::vec3> inNormals;
    Vector<glm::vec2> inUvs;
    Vector<glm::vec3> vertices;
    Vector<glm::vec3> normals;
    Vector<glm::vec2> uvs;
    Map<std::tuple<int, int, int>, int> indicesTrans;
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
                inVertices.push_back(v);
            } else if(lineType == "vn") {
                glm::vec3 n;
                ss >> n.x;
                ss >> n.y;
                ss >> n.z;
                //std::cout << n.x << " " << n.y << " " << n.z << std::endl;
                inNormals.push_back(n);
            } else if(lineType == "vt") {
                glm::vec2 uv;
                ss >> uv.x;
                ss >> uv.y;
                //std::cout << uv.x << " " << uv.y << std::endl;
                inUvs.push_back(uv);
            } else if(lineType == "f") {
                String lineTriangle;
                Vector<int> idxs;
                while(std::getline(ss, lineTriangle, ' ')) {
                    std::stringstream triss(lineTriangle);
                    String lineTrianglePoint;
                    if(lineTriangle.size() > 1) {
                        Vector<int> vertexIdxs;
                        while(std::getline(triss, lineTrianglePoint, '/')) {
                            if(!lineTrianglePoint.empty()) {
                                std::stringstream vss(lineTrianglePoint);
                                int i;
                                vss >> i;
                                vertexIdxs.push_back(i-1);
                                //std::cout << i << "/";
                            }
                        }
                        int i0 = (vertexIdxs.size() < 1 ? 0 : vertexIdxs[0]);
                        int i1 = (vertexIdxs.size() < 2 ? 0 : vertexIdxs[1]);
                        int i2 = (vertexIdxs.size() < 3 ? 0 : vertexIdxs[2]);
                        std::tuple<int, int, int> vertexIdx = {i0, i1, i2};
                        int i;
                        auto it = indicesTrans.find(vertexIdx);
                        if(it != indicesTrans.end()) {
                            i = it->second;
                        } else {
                            i = vertices.size();
                            vertices.push_back(inVertices[i0]);
                            uvs.push_back(inUvs[i1]);
                            normals.push_back(inNormals[i2]);
                        }
                        idxs.push_back(i);
                    }
                    //std::cout << " ";
                }
                if(idxs.size() >= 3) {
                    for(int i = 2; i < idxs.size(); i++) {
                        indices.push_back(idxs[0]);
                        indices.push_back(idxs[i-1]);
                        indices.push_back(idxs[i]);
                    }
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