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
    int quadIndicesCount = 6*(parallelCount - 1)*phiCount;
    int triIndicesCount = 3*phiCount;
    int indicesCount = quadIndicesCount + 2*triIndicesCount;
    int startQuads = 3*phiCount;
    int startUpTri = indicesCount - startQuads;
    Vector<glm::vec3> vertices(vertexCount);
    Vector<glm::vec2> uvs(vertexCount);
    Vector<int> indices(indicesCount);

    for(uint t = 0; t < thetaCount; t++) {
        float theta = M_PI * ((float)t) / (thetaCount-1);
        float sinTheta = glm::sin(theta);
        float mCosTheta = -glm::cos(theta);
        float uvY = (mCosTheta + 1) / 2;
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