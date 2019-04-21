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

File name: RenderInstance.cpp

*/

#include <RSEngine.h>

namespace rs {
    void Render::RenderInstance(std::shared_ptr<Instance> instance) {
        for (auto kid : instance->GetChildren()) {
            if (kid->ClassName == "Part") {
                GeometryGenerator gen;
                std::shared_ptr<Part> p = std::static_pointer_cast<Part>(kid);
                RenderPipeline* pipeline = nullptr;

                if (kid->renderID != INT_MAX) {
                    pipeline = pipelines.at(kid->renderID);

                    pipeline->VertexShader->Release();
                    pipeline->PixelShader->Release();
                    pipeline->VertexBuffer->Release();
                    pipeline->IndexBuffer->Release();

                    pipeline->VertexShader = nullptr;
                    pipeline->PixelShader = nullptr;
                    pipeline->VertexBuffer = nullptr;
                    pipeline->IndexBuffer = nullptr;
                }
                else {
                    pipeline = new RenderPipeline;
                }

                MeshData partMesh;
                gen.GenerateCube(p->Size, &partMesh);

                pipeline->ViewMatrix = DirectX::XMMatrixTranslation(p->Position.X, p->Position.Y, p->Position.Z);

                D3D11_BUFFER_DESC vertexBufferDesc;
                ZeroMemory(&vertexBufferDesc, sizeof(D3D11_BUFFER_DESC));
                vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
                vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
                vertexBufferDesc.ByteWidth = sizeof(MeshData::vertex) * partMesh.vertexMap.size();
                vertexBufferDesc.CPUAccessFlags = 0;

                D3D11_SUBRESOURCE_DATA resourceDataVertex;
                ZeroMemory(&resourceDataVertex, sizeof(D3D11_SUBRESOURCE_DATA));
                resourceDataVertex.pSysMem = &(partMesh.vertexMap.front());

                pdx_Device->CreateBuffer(&vertexBufferDesc, &resourceDataVertex, &pipeline->VertexBuffer);

                D3D11_BUFFER_DESC indexBufferDesc;
                ZeroMemory(&indexBufferDesc, sizeof(D3D11_BUFFER_DESC));
                indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
                indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
                indexBufferDesc.ByteWidth = sizeof(unsigned int) * partMesh.vertexIndices.size() * 3;
                indexBufferDesc.CPUAccessFlags = 0;

                D3D11_SUBRESOURCE_DATA irinitData;
                irinitData.pSysMem = &(partMesh.vertexIndices.front());;
                pdx_Device->CreateBuffer(&indexBufferDesc, &irinitData, &pipeline->IndexBuffer);

                LoadShader(ST_VertexShader, pipeline, "data/shaders/rshader_commonobj.shader");
                LoadShader(ST_PixelShader, pipeline, "data/shaders/rshader_commonobj.shader");

                pipeline->VertexCount = partMesh.vertexMap.size();
                pipeline->IndexCount = partMesh.vertexIndices.size();

                if (kid->renderID == INT_MAX) {
                    kid->renderID = pipelines.size();
                    pipelines.push_back(pipeline);
                }
            }
            if (kid->ClassName == "Material") {

            }
            if (kid->ClassName == "Texture") {

            }
            if (kid->ClassName == "MeshPart") {
                std::shared_ptr<MeshPart> bp = std::static_pointer_cast<MeshPart>(kid);
            }
            RenderInstance(kid);
        }
    }

} // namespace rs
