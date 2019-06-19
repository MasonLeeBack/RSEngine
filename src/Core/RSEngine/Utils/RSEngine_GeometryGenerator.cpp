/*

RSEngine
Copyright (c) 2019 Mason Lee Back

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

File name: RSGeometryGenerator.cpp

*/

#include <Utils/RSEngine_GeometryGenerator.h>
#include <Render/RSRender_Math.h>

namespace rs::Utils {
    MeshData GeometryGenerator::GenerateCube() {
        MeshData mesh;

        mesh.vertexMap =
        {
            { vertexPos::set(0, 1, 0), vertexCol::set(1, 1, 1, 1), vertexUV::set(0, 0, 0) },
            { vertexPos::set(1, 1, 0), vertexCol::set(1, 1, 1, 1), vertexUV::set(1, 0, 0) },
            { vertexPos::set(0, 0, 0), vertexCol::set(1, 1, 1, 1), vertexUV::set(0, 1, 0) },
            { vertexPos::set(1, 0, 0), vertexCol::set(1, 1, 1, 1), vertexUV::set(1, 1, 0) },
            { vertexPos::set(0, 1, 1), vertexCol::set(1, 1, 1, 1), vertexUV::set(0, 0, 1) },
            { vertexPos::set(1, 1, 1), vertexCol::set(1, 1, 1, 1), vertexUV::set(1, 0, 1) },
            { vertexPos::set(0, 0, 1), vertexCol::set(1, 1, 1, 1), vertexUV::set(0, 1, 1) },
            { vertexPos::set(1, 0, 1), vertexCol::set(1, 1, 1, 1), vertexUV::set(1, 1, 1) },
        };

        mesh.vertexIndices =
        {
            0, 1, 2,    // side 1
            2, 1, 3,
            4, 0, 6,    // side 2
            6, 0, 2,
            7, 5, 6,    // side 3
            6, 5, 4,
            3, 1, 7,    // side 4
            7, 1, 5,
            4, 5, 0,    // side 5
            0, 5, 1,
            3, 7, 2,    // side 6
            2, 7, 6,
        };

        return mesh;
    }

    MeshData GeometryGenerator::GenerateQuad() {
        MeshData mesh;

        mesh.vertexMap =
        {
            { vertexPos::set(0, 1, 0), vertexCol::set(1, 1, 1, 1), vertexUV::set(0, 1)},
            { vertexPos::set(1, 1, 0), vertexCol::set(1, 1, 1, 1), vertexUV::set(1, 1)},
            { vertexPos::set(0, 0, 0), vertexCol::set(1, 1, 1, 1), vertexUV::set(0, 0)},
            { vertexPos::set(1, 0, 0), vertexCol::set(1, 1, 1, 1), vertexUV::set(1, 0)},
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

        float dPhi = Render::RS_PI / (ring - 1);
        for (float phi = -Render::RS_PIDIV2; phi <= Render::RS_PIDIV2 + 0.00001f; phi += dPhi)
        {
            float y = rad * sinf(phi) + engOffset;
            float r = rad * cosf(phi);

            float dTheta = 2.0f*Render::RS_PI / slice;
            for (unsigned j = 0; j <= slice; j++)
            {
                vertex mVertex;
                float theta = j * dTheta;
                float x = r * cosf(theta) + engOffset;
                float z = r * sinf(theta) + engOffset;
                mVertex.pos = vertexPos::set(x, y, z);
                {
                    float u = (float)j / slice;
                    float v = (y + rad) / (2 * rad);
                    mVertex.texCoord = vertexUV::set(u, v);
                }

                mVertex.color = vertexCol::set(1, 1, 1, 1);

                mesh.vertexMap.push_back(mVertex);
            }

        }

        unsigned ringvc = slice + 1;
        for (unsigned int i = 0; i < ring; i++)
        {
            for (unsigned int j = 0; j < slice; j++)
            {
                mesh.vertexIndices.push_back(i*ringvc + j);
                mesh.vertexIndices.push_back((i + 1)*ringvc + j);
                mesh.vertexIndices.push_back((i + 1)*ringvc + j + 1);
                mesh.vertexIndices.push_back(i*ringvc + j);
                mesh.vertexIndices.push_back((i + 1)*ringvc + j + 1);
                mesh.vertexIndices.push_back(i*ringvc + j + 1);
            }
        }

        return mesh;
    }

} // namespace rs
