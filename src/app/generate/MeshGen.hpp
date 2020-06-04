/**
 * @file MeshGen.hpp
 * @author sadekpet
 * @brief 
 * @date 2020-03-07
 */

#ifndef PGR_MESH_GEN_HPP
#define PGR_MESH_GEN_HPP

#include <core/render/Primitives.hpp>

namespace sadekpet {

/**
 * @brief Obsahuje metody na procedurální generování jednoduchých modelů.
 * 
 */
class MeshGen {
private:
static uint sphere30vertCount;
static uint sphere30indicesCount;
static float sphere30vertices[];
static float sphere30uvs[];
static int sphere30indices[];

public:

static Mesh3D* BasicSphere(uint segmentation);
static Mesh3D* BasicSphere(uint meridianCount, uint parallelCount);
static Line3D* Cyrcle(float radius, uint segmentation);
static BasicMesh3D* BasicCube();
static Mesh3D* HardCodedSphere30();

private:
static void MakeQuad(int* outIndices, int v0, int v1, int v2, int v3);
};

}

#endif // PGR_MESH_GEN_HPP