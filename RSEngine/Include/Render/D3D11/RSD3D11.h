/*

RSEngine
Copyright (c) 2019 Mason Lee Back

File name: RSD3D11.h

*/

#pragma once
#ifndef _RSD3D11_h_
#define _RSD3D11_h_

#include "RSD3D11_Types.h"
#include "RSD3D11_TypeConv.h"
#include "RSD3D11_Buffer.h"
#include "RSD3D11_Shader.h"
#include "RSD3D11_Texture.h"

namespace rs::Render {
    class RSD3D11 : public RSRender {
    public:
        bool Initialize() override;
        void Update() override;
        void Shutdown() override;

        RSRenderTargetView CreateRenderTarget(RSRender_Texture* texture) override;
        void ClearRenderTarget(float color[4]) override;

        void ClearDepthStencil() override;

        RSRender_Texture* CreateTexture(const RSTextureDesc& desc) override;
        void DestroyTexture(RSRender_Texture* texture) override;

        RSRender_Buffer* CreateBuffer(const RSBufferDesc& desc) override;
        void DestroyBuffer(RSRender_Buffer* buffer) override;

        void SetShaderResource(RSShaderStage stage, RSShaderResourceView srv) override;
        void SetShaderSampler(RSShaderStage stage, RSShaderSamplerState sss) override;

        RSRender_Shader* CreateShaderFromFile(RSShaderStage stage, const char* fileName) override;
        RSRender_Shader* CreateShaderFromBlob(RSShaderStage stage, void* shaderBlob) override;
        void DestroyShader(RSRender_Shader* shader) override;

        void SetShader(RSRender_Shader* shader) override;

        void SetVertexBuffer(RSRender_Buffer* buf) override;
        void SetIndexBuffer(RSRender_Buffer* buf) override;

        void UpdateResolution(bool bIsEditor, float width, float height) override;

        void PresentSwapChain() override;

        void Draw(unsigned int vertexCount, RSPrimitiveTopology topology) override;
        void DrawIndexed(unsigned int indexCount, RSPrimitiveTopology topology) override;

        // DirectX specific functions for RSD3D11 objects
        ID3D11Device* getDevice();
        ID3D11DeviceContext* getDeviceContext();

    private:
        ID3D11Device* l_Device = nullptr;
        ID3D11DeviceContext* l_DeviceContext = nullptr;
        
        ID3D11RenderTargetView* l_RenderTarget = nullptr;

        ID3D11Texture2D* l_DepthStencilTexture = nullptr;
        ID3D11DepthStencilView* l_DepthStencil = nullptr;
        
        IDXGISwapChain* l_SwapChain = nullptr;

        RSD3D11_TypeConv conv;
    };
}

#endif
