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

namespace rs {
    INITIALIZE_INSTANCE_SOURCE(Part);

    void Part::render() {

        if (pipeline == nullptr) {
            pipeline = new RenderPipeline;

            MeshData partMesh;
            GeometryGenerator gen;
            gen.GenerateCube(Vector3(1, 1, 1), &partMesh);

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

            g_Renderer->LoadShader(ST_VertexShader, pipeline, "data/shaders/rshader_commonobj.shader");
            g_Renderer->LoadShader(ST_PixelShader, pipeline, "data/shaders/rshader_commonobj.shader");

            pipeline->VertexCount = partMesh.vertexMap.size();
            pipeline->IndexCount = partMesh.vertexIndices.size();
        }

        pipeline->ViewMatrix = DirectX::XMMatrixScaling(Size.X, Size.Y, Size.Z);
        pipeline->ViewMatrix *= DirectX::XMMatrixTranslation(Position.X, Position.Y, Position.Z);

        if (pipeline->VertexShader)
            pdx_DeviceContext->VSSetShader(pipeline->VertexShader, 0, 0);
        if (pipeline->PixelShader)
            pdx_DeviceContext->PSSetShader(pipeline->PixelShader, 0, 0);
        // HS, TS, etc.

        // fix
        constantBuffer.WVP = pipeline->ViewMatrix * g_cameraMatrix.viewMatrix * g_cameraMatrix.projMatrix;
        constantBuffer.WVP = XMMatrixTranspose(constantBuffer.WVP);
        pdx_DeviceContext->UpdateSubresource(pdx_ConstantBuffer, 0, NULL, &constantBuffer, 0, 0);
        pdx_DeviceContext->VSSetConstantBuffers(0, 1, &pdx_ConstantBuffer);

        if (pipeline->InputLayout)
            pdx_DeviceContext->IASetInputLayout(pipeline->InputLayout);

        pdx_DeviceContext->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
        UINT stride = sizeof(MeshData::vertex);
        UINT offset = 0;
        pdx_DeviceContext->IASetVertexBuffers(0, 1, &pipeline->VertexBuffer, &stride, &offset);

        pdx_DeviceContext->IASetIndexBuffer(pipeline->IndexBuffer, DXGI_FORMAT_R32_UINT, 0);
        pdx_DeviceContext->DrawIndexed(pipeline->IndexCount, 0, 0);

        renderChildren();
    }

} // namespace RS

