/*

RSEngine
Copyright (c) 2019 Mason Lee Back

File name: RSGNM.h

*/

#ifdef _ORBIS

#ifndef _RSGNM_h_
#define _RSGNM_h_

#include <gnm.h>

#include <Render/RSRender.h>

namespace rs::Render {
    class RSGNM : public RSRender {
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
    };

} // namespace rs::Render

#endif // _RSGNM_h_

#endif // _ORBIS