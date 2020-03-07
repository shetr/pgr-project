#include "MeshGen.hpp"

namespace sadekpet {


Mesh3D* MeshGen::BasicSphere(uint segmentation)
{
    return BasicSphere(segmentation, segmentation);
}
Mesh3D* MeshGen::BasicSphere(uint meridianCount, uint parallelCount)
{
    uint phiCount = meridianCount + 2;
    uint thetaCount = parallelCount + 2;
    int vertexCount = 2 + parallelCount*phiCount;
    int indicesCount = 6*(parallelCount - 1)*phiCount + 3*2*phiCount;
    Vector<glm::vec3> vertices(vertexCount);
    Vector<glm::vec2> uvs(vertexCount);
    Vector<int> indices(indicesCount);

    vertices[0] = glm::vec3(0,1,0);
    vertices[vertexCount-1] = glm::vec3(0,-1,0);

    for(uint t = 1; t < thetaCount - 1; t++) {
        for(uint p = 0; p < phiCount; p++) {
            uint v = 1 + p + phiCount*(t-1);
            float phi =  2 * M_PI * ((float)p) / phiCount;
            float theta = M_PI * ((float)t) / thetaCount;
            float sinPhi = glm::sin(phi);
            float cosPhi = glm::cos(phi);
            float sinTheta = glm::sin(theta);
            float cosTheta = glm::cos(theta);
            vertices[v].x = sinTheta * cosPhi;
            vertices[v].y = sinTheta * sinPhi;
            vertices[v].z = cosTheta;

            
        }
    }



    return new Mesh3D(vertexCount, indicesCount, vertices.data(), uvs.data(), vertices.data(), indices.data());
}

}