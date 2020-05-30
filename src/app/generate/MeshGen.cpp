#include "MeshGen.hpp"

#include <iostream>
#include <core/Console.hpp>

namespace sadekpet {


Mesh3D* MeshGen::BasicSphere(uint segmentation)
{
    return BasicSphere(segmentation, segmentation);
}
Mesh3D* MeshGen::BasicSphere(uint meridianCount, uint parallelCount)
{
    uint phiCount = meridianCount + 2;
    uint thetaCount = parallelCount + 2;
    int vertexCount = thetaCount*phiCount;
    int quadIndicesCount = 6*(parallelCount - 1)*phiCount;
    int triIndicesCount = 3*phiCount;
    int indicesCount = quadIndicesCount + 2*triIndicesCount;
    int startQuads = 3*phiCount;
    int startUpTri = indicesCount - startQuads;
    Vector<glm::vec3> vertices(vertexCount);
    Vector<glm::vec2> uvs(vertexCount);
    Vector<int> indices(indicesCount);

    for(uint t = 0; t < thetaCount; t++) {
        float tRatio = ((float)t) / (thetaCount-1);
        float theta = M_PI * tRatio;
        float sinTheta = glm::sin(theta);
        float mCosTheta = -glm::cos(theta);
        //float uvY = (mCosTheta + 1) / 2;
        float uvY = tRatio;
        for(uint p = 0; p < phiCount; p++) {
            uint v = p + phiCount*t;
            float pRatio = ((float)p) / (phiCount-1);
            float phi =  2 * M_PI * pRatio;
            float sinPhi = glm::sin(phi);
            float cosPhi = glm::cos(phi);

            vertices[v].x = sinTheta * cosPhi;
            vertices[v].y = mCosTheta;
            vertices[v].z = sinTheta * sinPhi;


            uvs[v].x = pRatio;
            uvs[v].y = uvY;
        }
    }
    for(uint v = 0; v < phiCount; v++) {
        int i = 3*v;
        indices[i+0] = v;
        indices[i+1] = v + phiCount;
        indices[i+2] = (v + 1) % phiCount + phiCount;
    }
    for(uint t = 1; t < thetaCount - 2; t++) {
        for(uint p = 0; p < phiCount; p++) {
            uint v = p + phiCount*t;
            uint vp1 = (p + 1)% phiCount + phiCount*t;
            uint i = (v - phiCount) * 6 + triIndicesCount;
            MakeQuad(&indices[i], v, v + phiCount, vp1 + phiCount, vp1);
        }
    }
    for(uint p = 0; p < phiCount; p++) {
        int i = triIndicesCount + quadIndicesCount + 3*p;
        int v = (thetaCount - 2)*phiCount + p;
        int vp1 = (thetaCount - 2)*phiCount + (p + 1) % phiCount;
        indices[i+0] = vp1;
        indices[i+1] = v;
        indices[i+2] = v + phiCount;
    }

    return new Mesh3D(vertexCount, indicesCount, vertices.data(), uvs.data(), vertices.data(), indices.data());
}

Line3D* MeshGen::Cyrcle(float radius, uint segmentation)
{
    int vertexCount = segmentation+1;
    int indicesCount = 2*segmentation;
    Vector<glm::vec3> vertices(vertexCount);
    Vector<int> indices(indicesCount);
    for(int i = 0; i < vertexCount; i++) {
        float phi =  2 * M_PI * ((float)i) / segmentation;
        vertices[i] = radius * glm::vec3(glm::cos(phi), 0, glm::sin(phi));
        if(i < segmentation) {
            indices[2*i] = i;
            indices[2*i+1] = i+1;
        }
    }
    return new Line3D(vertexCount, indicesCount, vertices.data(), indices.data());
}

BasicMesh3D* MeshGen::BasicCube()
{
    Vector<glm::vec3> vertices = {
        glm::vec3(-1, -1, -1),
        glm::vec3( 1, -1, -1),
        glm::vec3( 1, -1,  1),
        glm::vec3(-1, -1,  1),
        glm::vec3(-1,  1, -1),
        glm::vec3( 1,  1, -1),
        glm::vec3( 1,  1,  1),
        glm::vec3(-1,  1,  1)
    };
    Vector<int> indices(6*6);
    MakeQuad(&indices[0*6], 3, 2, 1, 0);
    MakeQuad(&indices[1*6], 4, 5, 6, 7);
    MakeQuad(&indices[2*6], 5, 4, 0, 1);
    MakeQuad(&indices[3*6], 6, 5, 1, 2);
    MakeQuad(&indices[4*6], 7, 6, 2, 3);
    MakeQuad(&indices[5*6], 4, 7, 3, 0);
    return new BasicMesh3D(vertices.size(), indices.size(), vertices.data(), indices.data());
}

Mesh3D* MeshGen::HardCodedSphere30()
{
    return new Mesh3D(sphere30vertCount, sphere30indicesCount, 
        (glm::vec3*)sphere30vertices, 
        (glm::vec2*)sphere30uvs, 
        (glm::vec3*)sphere30vertices, 
        sphere30indices);
}

void MeshGen::MakeQuad(int* outIndices, int v0, int v1, int v2, int v3)
{
    outIndices[0] = v0;
    outIndices[1] = v1;
    outIndices[2] = v2;
    outIndices[3] = v0;
    outIndices[4] = v2;
    outIndices[5] = v3;
}

}