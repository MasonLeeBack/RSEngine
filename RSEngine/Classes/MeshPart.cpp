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

File name: MeshPart.cpp

*/

#include <Classes/MeshPart.h>
#include <Renderer/RSRender.h>
using namespace rs::Renderer;
#include <Renderer/RSGeometryGenerator.h>
#include <Renderer/LoadModel_OBJ.h>

namespace rs {
    INITIALIZE_INSTANCE_SOURCE(MeshPart);

    void MeshPart::render() {

        if (pipeline == nullptr) {
            pipeline = new RSRenderPipeline;
            MeshData partMesh;

            if (MeshFile == "") {
                GeometryGenerator gen;
                partMesh = gen.GenerateCube();
            }
            else {
                ObjLoader loader;
                loader.LoadModel(&partMesh, MeshFile.c_str());
            }

            RSBufferDesc vertDesc;
            vertDesc.mType = RSBufferType::VERTEX_BUFFER;
            vertDesc.mElementCount = partMesh.vertexMap.size();
            vertDesc.mStride = sizeof(vertex);

            pipeline->VertexBuffer = new RSRender_Buffer(vertDesc);
            pipeline->VertexBuffer->Initialize(&(partMesh.vertexMap.front()));

            RSBufferDesc indexDesc;
            indexDesc.mType = RSBufferType::INDEX_BUFFER;
            indexDesc.mElementCount = partMesh.vertexIndices.size();
            indexDesc.mStride = sizeof(unsigned int);

            pipeline->IndexBuffer = new RSRender_Buffer(indexDesc);
            pipeline->IndexBuffer->Initialize(&(partMesh.vertexIndices.front()));

            RSBufferDesc vsConstDesc;
            vsConstDesc.mType = RSBufferType::CONST_BUFFER;
            vsConstDesc.mElementCount = 1;
            vsConstDesc.mStride = sizeof(vsConst_PerObject);

            pipeline->ObjectConstant = new RSRender_Buffer(vsConstDesc);
            pipeline->ObjectConstant->Initialize(&pipeline->objectVSConst);

            RSBufferDesc psConstDesc;
            psConstDesc.mType = RSBufferType::CONST_BUFFER;
            psConstDesc.mElementCount = 1;
            psConstDesc.mStride = sizeof(psConst_PerObject);

            pipeline->pixelConst = new RSRender_Buffer(psConstDesc);
            pipeline->pixelConst->Initialize(&pipeline->objectPSConst);

            ZeroMemory(&pipeline->objectPSConst, sizeof(psConst_PerObject));

            D3D11_INPUT_ELEMENT_DESC inputElement[] = {
                {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
                {"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
                { "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 20, D3D11_INPUT_PER_VERTEX_DATA, 0}
            };

            pipeline->VertexShader = new RSRender_Shader(RSShaderType::RS_VERTEX_SHADER, inputElement, _ARRAYSIZE(inputElement));
            pipeline->VertexShader->InitializeShaderFromFile("data/shaders/shader_common_vs.hlsl");

            pipeline->PixelShader = new RSRender_Shader(RSShaderType::RS_PIXEL_SHADER, nullptr, 0);
            pipeline->PixelShader->InitializeShaderFromFile("data/shaders/shader_common_ps.hlsl");

            pipeline->VertexCount = partMesh.vertexMap.size();
            pipeline->IndexCount = partMesh.vertexIndices.size();
        }

        DirectX::XMMATRIX worldMatrix;
        worldMatrix = DirectX::XMMatrixScaling(Size.X, Size.Y, Size.Z);
        worldMatrix *= DirectX::XMMatrixRotationX(DirectX::XMConvertToRadians(Rotation.X));
        worldMatrix *= DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(Rotation.Y));
        worldMatrix *= DirectX::XMMatrixRotationZ(DirectX::XMConvertToRadians(Rotation.Z));
        worldMatrix *= DirectX::XMMatrixTranslation(Position.X, Position.Y, Position.Z);

        g_RSRender->AssignShader(pipeline->VertexShader);
        g_RSRender->AssignShader(pipeline->PixelShader);
        // HS, TS, etc.

        pipeline->objectVSConst.world = DirectX::XMMatrixTranspose(worldMatrix);
        pipeline->objectPSConst.isTextured = pipeline->Texture.DrawTexture;

        g_RSRender->l_DeviceContext->UpdateSubresource(pipeline->ObjectConstant->mpGPUData, 0, NULL, &pipeline->objectVSConst, 0, 0);
        g_RSRender->l_DeviceContext->VSSetConstantBuffers(1, 1, &pipeline->ObjectConstant->mpGPUData);

        g_RSRender->l_DeviceContext->UpdateSubresource(pipeline->pixelConst->mpGPUData, 0, NULL, &pipeline->objectPSConst, 0, 0);
        g_RSRender->l_DeviceContext->PSSetConstantBuffers(1, 1, &pipeline->pixelConst->mpGPUData);

        if (pipeline->Texture.DrawTexture == true) {
            g_RSRender->l_DeviceContext->PSSetSamplers(0, 1, &pipeline->Texture.SamplerState);
            g_RSRender->l_DeviceContext->PSSetShaderResources(0, 1, &pipeline->Texture.Texture);
        }
        else {
            ID3D11ShaderResourceView* nullSRV = { nullptr };
            g_RSRender->l_DeviceContext->PSSetShaderResources(0, 1, &nullSRV);
        }

        g_RSRender->l_DeviceContext->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
        UINT stride = sizeof(vertex);
        UINT offset = 0;
        g_RSRender->l_DeviceContext->IASetVertexBuffers(0, 1, &pipeline->VertexBuffer->mpGPUData, &stride, &offset);

        g_RSRender->l_DeviceContext->IASetIndexBuffer(pipeline->IndexBuffer->mpGPUData, DXGI_FORMAT_R32_UINT, 0);
        g_RSRender->l_DeviceContext->DrawIndexed(pipeline->IndexCount, 0, 0);

        renderChildren();
    }

} // namespace RS

