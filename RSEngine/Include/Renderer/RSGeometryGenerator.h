/*

RSEngine
Copyright (c) 2020 Mason Lee Back

File name: RSGeometryGenerator.h

*/

#pragma once
#ifndef _RSGeometryGenerator_h_
#define _RSGeometryGenerator_h_

#include <Types/MeshData.h>

namespace rs {
    class GeometryGenerator {
    public:
        MeshData GenerateCube();
        MeshData GenerateQuad();
        MeshData GenerateFullscreenQuad();

        MeshData GenerateSphere(float rad, float ring, float slice);
    };
} // namespace rs

#endif // _RSGeometryGenerator_h_
