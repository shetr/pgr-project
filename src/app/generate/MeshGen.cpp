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
    int vertexCount = thetaCount*phiCount;
    int indicesCount = 6*(parallelCount - 1)*phiCount + 3*2*phiCount;
    int startQuads = 3*phiCount;
    int startUpTri = indicesCount - startQuads;
    Vector<glm::vec3> vertices(vertexCount);
    Vector<glm::vec2> uvs(vertexCount);
    Vector<int> indices(indicesCount);

    for(uint t = 0; t < thetaCount; t++) {
        float theta = M_PI * ((float)t) / thetaCount;
        float sinTheta = glm::sin(theta);
        float mCosTheta = -glm::cos(theta);
        float uvY = (mCosTheta + 1) / 2;
        for(uint p = 0; p < phiCount; p++) {
            uint v = p + phiCount*t;
            float pRatio = ((float)p) / phiCount;
            float phi =  2 * M_PI * pRatio;
            float sinPhi = glm::sin(phi);
            float cosPhi = glm::cos(phi);

            vertices[v].x = sinTheta * cosPhi;
            vertices[v].y = sinTheta * sinPhi;
            vertices[v].z = mCosTheta;

            uvs[v].y = uvY;
            if(p==0 || p==phiCount-1) {
                uvs[v].x = ((float)(2*p + 1)) / (2*phiCount);
            } else {
                uvs[v].x = pRatio;
            }
            
            if(v < phiCount) {
                int i = v*3;
                indices[i+0] = v;
                indices[i+1] = v + phiCount;
                indices[i+2] = v + phiCount + 1;
            } else if(v < vertexCount - 2 * phiCount) {
                int i = startQuads + (parallelCount - 1)*p*6;
                MakeQuad(&indices[i], v, v + phiCount, v + phiCount + 1, v + 1);
            } else if(v > vertexCount - phiCount) {
                int i = startUpTri + p*3;
                indices[i+0] = v - phiCount;
                indices[i+1] = v - phiCount + 1;
                indices[i+2] = v;
            }

        }
    }

    return new Mesh3D(vertexCount, indicesCount, vertices.data(), uvs.data(), vertices.data(), indices.data());
}


void MeshGen::MakeQuad(int* outIndices, int v0, int v1, int v2, int v3)
{
    outIndices[0] = v0;
    outIndices[1] = v1;
    outIndices[2] = v2;
    outIndices[0] = v0;
    outIndices[2] = v2;
    outIndices[3] = v3;
}

}