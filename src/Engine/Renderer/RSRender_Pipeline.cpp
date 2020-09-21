/*

RSEngine
Copyright (c) 2020 Mason Lee Back

File name: RSRender_Pipeline.cpp

*/

#include <Renderer/RSRender.h>

namespace rs::Renderer{
    RSRender_Buffer* RSRenderPipeline::getVSConstBuffer(int index)
    {
        return vsConstantObjects[index].vsConstantBuffer;
    }

    RSRender_Buffer* RSRenderPipeline::getPSConstBuffer(int index)
    {
        return psConstantObjects[index].vsConstantBuffer;
    }

    bool RSRenderPipeline::createBuffersForMesh(MeshData data)
    {
        // TODO: return false if a buffer fails to be created
        RSBufferDesc vertDesc;
        vertDesc.mType = RSBufferType::VERTEX_BUFFER;
        vertDesc.mElementCount = data.vertexMap.size();
        vertDesc.mStride = sizeof(vertex);

        VertexBuffer = new RSRender_Buffer(vertDesc);
        VertexBuffer->Initialize(data.vertexMap.ptr());

        RSBufferDesc indexDesc;
        indexDesc.mType = RSBufferType::INDEX_BUFFER;
        indexDesc.mElementCount = data.vertexIndices.size();
        indexDesc.mStride = sizeof(unsigned int);

        IndexBuffer = new RSRender_Buffer(vertDesc);
        IndexBuffer->Initialize(data.vertexIndices.ptr());

        VertexCount = data.vertexMap.size();
        IndexCount = data.vertexIndices.size();

        return true;
    }

    void RSRenderPipeline::Draw(bool isAlphaPass)
    {
        if (alpha > 0.0f && !isAlphaPass) {
            g_RSRender->AddToAlphaPass(this);
            return;
        }

        if (alpha > 1.0f) {
            // Don't bother drawing a transparent object for right now
            return;
        }

        // Check to see whether or not we have our vertex shaders
        if (VertexShader) {
            g_RSRender->AssignShader(VertexShader);
        }
        if (PixelShader) {
            g_RSRender->AssignShader(PixelShader);
        }

        // We use this as an offset, adjust if the engine has its own constant buffers
        int vsObjectCount = 1;
        for (auto constKid : vsConstantObjects) {
            g_RSRender->l_DeviceContext->VSSetConstantBuffers(vsObjectCount, 1, &constKid.vsConstantBuffer->mpGPUData);
            vsObjectCount++;
        }

        // We use this as an offset, adjust if the engine has its own constant buffers
        int psObjectCount = 1;
        for (auto constKid : psConstantObjects) {
            g_RSRender->l_DeviceContext->PSSetConstantBuffers(psObjectCount, 1, &constKid.vsConstantBuffer->mpGPUData);
            psObjectCount++;
        }

        g_RSRender->SetTransparency(alpha);

        g_RSRender->l_DeviceContext->VSSetConstantBuffers(1, 1, &ObjectConstant->mpGPUData);
        g_RSRender->l_DeviceContext->PSSetConstantBuffers(1, 1, &pixelConst->mpGPUData);

        // Set the rasterizer state
        g_RSRender->SetCullState(cullState);

        if (Texture.DrawTexture == true) {
            g_RSRender->l_DeviceContext->PSSetSamplers(0, 1, &Texture.SamplerState);
            g_RSRender->l_DeviceContext->PSSetShaderResources(0, 1, &Texture.Texture);
        }
        else {
            ID3D11ShaderResourceView* nullSRV = { nullptr };
            g_RSRender->l_DeviceContext->PSSetShaderResources(0, 1, &nullSRV);
        }
        
        g_RSRender->l_DeviceContext->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
        UINT stride = sizeof(vertex);
        UINT offset = 0;
        g_RSRender->l_DeviceContext->IASetVertexBuffers(0, 1, &VertexBuffer->mpGPUData, &stride, &offset);

        g_RSRender->l_DeviceContext->IASetIndexBuffer(IndexBuffer->mpGPUData, DXGI_FORMAT_R32_UINT, 0);
        g_RSRender->l_DeviceContext->DrawIndexed(IndexCount, 0, 0);
    }

} // namespace rs::Renderer
