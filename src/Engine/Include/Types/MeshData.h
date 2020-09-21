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

File name: MeshData.h

*/

#pragma once
#ifndef _MeshData_h_
#define _MeshData_h_

#include <Types\RSArray.h>

namespace rs {

    struct vertexPos {
        union {
            struct {
                float x;
                float y;
                float z;
            };
            float v[3];
        };
        
        static vertexPos set(float x, float y, float z) { vertexPos temp; temp.x = x; temp.y = y; temp.z = z; return temp; }

        bool operator==(const vertexPos& other) const {
            return x == other.x && y == other.y && z == other.z;
        }
    };

    struct vertexUV {
        union {
            struct {
                float u;
                float v;
            };
            float t[2];
        };

        static vertexUV set(float u, float v) { vertexUV temp; temp.u = u; temp.v = v; return temp; }

        bool operator==(const vertexUV& other) const {
            return u == other.u && v == other.v;
        }
    };

    struct vertexNorm {
        union {
            struct {
                float x;
                float y;
                float z;
            };
            float v[3];
        };

        static vertexNorm set(float x, float y, float z) { vertexNorm temp; temp.x = x; temp.y = y; temp.z = z; return temp; }

        bool operator==(const vertexNorm& other) const {
            return x == other.x && y == other.y && z == other.z;
        }
    };

    struct vertex {
        vertexPos position;
        vertexNorm normal;
        vertexUV texCoord;

        bool operator==(const vertex& other) const {
            return position == other.position && normal == other.normal && texCoord == other.texCoord;
        }
    };

    struct MeshData {
        RSArray<vertex>         vertexMap;
        RSArray<unsigned int>   vertexIndices;
    };

} // namespace rs



#endif // _MeshData_h_
