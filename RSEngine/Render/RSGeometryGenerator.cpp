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

#include <RSEngine.h>

namespace rs {
    void GeometryGenerator::GenerateCube(Vector3 Size, MeshData* mesh) {
        mesh->vertexMap =
        {
            { 0.0f, Size.Y, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f },
            { Size.X, Size.Y, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f },
            { 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f },
            { Size.X, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f },
            { 0.0f, Size.Y, Size.Z, 0.0f, 0.0f, 1.0f, 1.0f },
            { Size.X, Size.Y, Size.Z, 1.0f, 0.0f, 0.0f, 1.0f },
            { 0.0f, 0.0f, Size.Z, 0.0f, 1.0f, 0.0f, 1.0f, },
            { Size.X, 0.0f, Size.Z, 0.0f, 1.0f, 1.0f, 1.0f, },
        };

        mesh->vertexIndices =
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
    }

} // namespace rs
