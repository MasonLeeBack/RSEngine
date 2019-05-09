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

File name: Part.cpp

*/

#include <RSEngine.h>

using namespace rs::Render;
using namespace rs::Utils;

namespace rs {
    INITIALIZE_INSTANCE_SOURCE(Part);

    void Part::render() {

        if (pipeline == nullptr) {
            pipeline = new Utils::RenderPipeline;

            GeometryGenerator gen;
            MeshData partMesh = gen.GenerateCube();

            RSBufferDesc vertexDesc;
            vertexDesc.id = RS_VERTEX_BUFFER;
            vertexDesc.uByteWidth = sizeof(vertex) * partMesh.vertexMap.size();
            vertexDesc.uStride = sizeof(vertex);
            vertexDesc.uOffset = 0;

            pipeline->vertexBuffer = g_Renderer->CreateBuffer(vertexDesc);
            pipeline->vertexBuffer->SetBuffer(&(partMesh.vertexMap.front()));

            RSBufferDesc indexDesc;
            indexDesc.id = RS_INDEX_BUFFER;
            indexDesc.uByteWidth = sizeof(unsigned int) * partMesh.vertexIndices.size() * 3;

            pipeline->indexBuffer = g_Renderer->CreateBuffer(indexDesc);
            pipeline->indexBuffer->SetBuffer(&(partMesh.vertexIndices.front()));
            pipeline->indexCount = partMesh.vertexIndices.size();

            pipeline->vertexShader = g_Renderer->CreateShaderFromFile(RS_SHADER_STAGE_VS, "data/shaders/part_vs.rsfx");
            pipeline->pixelShader = g_Renderer->CreateShaderFromFile(RS_SHADER_STAGE_PS, "data/shaders/part_ps.rsfx");
        }

        pipeline->DrawPipeline();

        renderChildren();
    }

} // namespace RS

