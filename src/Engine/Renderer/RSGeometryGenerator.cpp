/*

RSEngine
Copyright (c) 2020 Mason Lee Back

File name: RSGeometryGenerator.cpp

*/

#include <Renderer/RSGeometryGenerator.h>
#include <Types/RSRenderMath.h>

#include <math.h>

namespace rs {
    MeshData GeometryGenerator::GenerateCube() {
        MeshData mesh;

        mesh.vertexMap =
        {
            { vertexPos::set(-.5, .5, .5)   , vertexNorm::set(-.5, .5, .5)   , vertexUV::set(0,0) },
            { vertexPos::set(.5, .5, .5)    , vertexNorm::set(.5, .5, .5)    , vertexUV::set(1,0) },
            { vertexPos::set(.5, .5, -.5)   , vertexNorm::set(.5, .5, -.5)   , vertexUV::set(1,1) },
            { vertexPos::set(-.5, .5, -.5)  , vertexNorm::set(-.5, .5, -.5)  , vertexUV::set(0,1) },
            { vertexPos::set(-.5, .5, -.5)  , vertexNorm::set(-.5, .5, -.5)  , vertexUV::set(0,0) },
            { vertexPos::set(.5, .5, -.5)   , vertexNorm::set(.5, .5, -.5)   , vertexUV::set(1,0) },
            { vertexPos::set(.5, -.5, -.5)  , vertexNorm::set(.5, -.5, -.5)  , vertexUV::set(1,1) },
            { vertexPos::set(-.5, -.5, -.5) , vertexNorm::set(-.5, -.5, -.5) , vertexUV::set(0,1) },
            { vertexPos::set(.5, .5, -.5)   , vertexNorm::set(.5, .5, -.5)   , vertexUV::set(0,0) },
            { vertexPos::set(.5, .5, .5)    , vertexNorm::set(.5, .5, .5)    , vertexUV::set(1,0) },
            { vertexPos::set(.5, -.5, .5)   , vertexNorm::set(.5, -.5, .5)   , vertexUV::set(1,1) },
            { vertexPos::set(.5, -.5, -.5)  , vertexNorm::set(.5, -.5, -.5)  , vertexUV::set(0,1) },
            { vertexPos::set(.5, .5, .5)    , vertexNorm::set(.5, .5, .5)    , vertexUV::set(0,0) },
            { vertexPos::set(-.5, .5, .5)   , vertexNorm::set(-.5, .5, .5)   , vertexUV::set(1,0) },
            { vertexPos::set(-.5, -.5, .5)  , vertexNorm::set(-.5, -.5, .5)  , vertexUV::set(1,1) },
            { vertexPos::set(.5, -.5, .5)   , vertexNorm::set(.5, -.5, .5)   , vertexUV::set(0,1) },
            { vertexPos::set(-.5, .5, .5)   , vertexNorm::set(-.5, .5, .5)   , vertexUV::set(0,0) },
            { vertexPos::set(-.5, .5, -.5)  , vertexNorm::set(-.5, .5, -.5)  , vertexUV::set(1,0) },
            { vertexPos::set(-.5, -.5, -.5) , vertexNorm::set(-.5, -.5, -.5) , vertexUV::set(1,1) },
            { vertexPos::set(-.5, -.5, .5)  , vertexNorm::set(-.5, -.5, .5)  , vertexUV::set(0,1) },
            { vertexPos::set(.5, -.5, -.5)  , vertexNorm::set(.5, -.5, -.5)  , vertexUV::set(1,0) },
            { vertexPos::set(-.5, -.5, -.5) , vertexNorm::set(-.5, -.5, -.5) , vertexUV::set(0,0) },
            { vertexPos::set(-.5, -.5, .5)  , vertexNorm::set(-.5, -.5, .5)  , vertexUV::set(0,1) },
            { vertexPos::set(.5, -.5, .5)   , vertexNorm::set(.5, -.5, .5)   , vertexUV::set(1,1) },
        };

        mesh.vertexIndices =
        {
            0, 1, 2, 0, 2, 3,
            4, 5, 6, 4, 6, 7,
            8, 9, 10, 8, 10, 11,
            12, 13, 14, 12, 14, 15,
            16, 17, 18, 16, 18, 19,
            20, 22, 21, 20, 23, 22,
        };

        return mesh;
    }

    MeshData GeometryGenerator::GenerateQuad() {
        MeshData mesh;

        mesh.vertexMap =
        {
            { vertexPos::set(0, 1, 0), vertexNorm::set(-.5, .5, .5), vertexUV::set(0, 0)},
            { vertexPos::set(1, 1, 0), vertexNorm::set(-.5, .5, .5), vertexUV::set(1, 0)},
            { vertexPos::set(0, 0, 0), vertexNorm::set(-.5, .5, .5), vertexUV::set(0, 1)},
            { vertexPos::set(1, 0, 0), vertexNorm::set(-.5, .5, .5), vertexUV::set(1, 1)},
        };

        mesh.vertexIndices =
        {
            0, 1, 2,
            2, 1, 3
        };

        return mesh;
    }

    MeshData GeometryGenerator::GenerateFullscreenQuad() {
        MeshData mesh;

        mesh.vertexMap =
        {
            { vertexPos::set(-1, 1, 0),  vertexNorm::set(-.5, .5, .5), vertexUV::set(0, 0)},
            { vertexPos::set(1, 1, 0),   vertexNorm::set(-.5, .5, .5), vertexUV::set(1, 0)},
            { vertexPos::set(-1, -1, 0), vertexNorm::set(-.5, .5, .5), vertexUV::set(0, 1)},
            { vertexPos::set(1, -1, 0),  vertexNorm::set(-.5, .5, .5), vertexUV::set(1, 1)},
        };

        mesh.vertexIndices =
        {
            0, 1, 2,
            2, 1, 3
        };

        return mesh;
    }

    MeshData GeometryGenerator::GenerateSphere(float rad, float ring, float slice) {
        
        MeshData mesh;
        float engOffset = 0.5f;

        float dPhi = RS_PI / (ring - 1);
        for (float phi = -RS_PIDIV2; phi <= RS_PIDIV2 + 0.00001f; phi += dPhi)
        {
            float y = rad * sinf(phi) + engOffset;
            float r = rad * cosf(phi);

            float dTheta = 2.0f*RS_PI / slice;
            for (unsigned j = 0; j <= slice; j++)
            {
                vertex mVertex;
                float theta = j * dTheta;
                float x = r * cosf(theta) + engOffset;
                float z = r * sinf(theta) + engOffset;
                mVertex.position = vertexPos::set(x-.5f, y-.5f, z-.5f);
                {
                    float u = (float)j / slice;
                    float v = (y + rad) / (2 * rad);
                    mVertex.texCoord = vertexUV::set(u, v);
                }

                mesh.vertexMap.push(mVertex);
            }

        }

        unsigned int ringvc = static_cast<unsigned int>(slice) + 1;
        for (unsigned int i = 0; i < ring; i++)
        {
            for (unsigned int j = 0; j < slice; j++)
            {
                mesh.vertexIndices.push(i*ringvc + j);
                mesh.vertexIndices.push((i + 1)*ringvc + j);
                mesh.vertexIndices.push((i + 1)*ringvc + j + 1);
                mesh.vertexIndices.push(i*ringvc + j);
                mesh.vertexIndices.push((i + 1)*ringvc + j + 1);
                mesh.vertexIndices.push(i*ringvc + j + 1);
            }
        }

        return mesh;
    }

} // namespace rs
