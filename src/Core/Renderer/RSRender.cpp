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

File name: RSRender.cpp

*/

#include <Render/RSRender.h>
#include <Render/D3D11/RSD3D11.h>

#include <Classes/EngineClass.h>

float renderResX = 0.0f;
float renderResY = 0.0f;

namespace rs::Render {

    RSRender* g_CurrentRenderer;

    bool RSRender::Initialize() {
#ifdef _WIN32
        g_CurrentRenderer = new RSD3D11;

        return g_CurrentRenderer->Initialize();
#endif
#ifdef _ORBIS
        g_CurrentRenderer = new RSGNM;

        return g_CurrentRenderer->Initialize();
#endif
    }

    void RSRender::Update() {
        float color[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
        g_CurrentRenderer->ClearRenderTarget(color);
        g_CurrentRenderer->ClearDepthStencil();

        g_CurrentRenderer->Update();

        //eng->render();
        
        g_CurrentRenderer->PresentSwapChain();
    }

    void RSRender::Shutdown() {
        g_CurrentRenderer->Shutdown();

        delete g_CurrentRenderer;
        g_CurrentRenderer = nullptr;
    }

    RSRenderTargetView RSRender::CreateRenderTarget(RSRender_Texture* texture) {
        return g_CurrentRenderer->CreateRenderTarget(texture);
    }

    void RSRender::ClearRenderTarget(float color[4]) {
        g_CurrentRenderer->ClearRenderTarget(color);
    }

    void RSRender::ClearDepthStencil() {
        g_CurrentRenderer->ClearDepthStencil();
    }

    RSRender_Texture* RSRender::CreateTexture(const RSTextureDesc& desc) {
        return g_CurrentRenderer->CreateTexture(desc);
    }

    void RSRender::DestroyTexture(RSRender_Texture* texture) {
        g_CurrentRenderer->DestroyTexture(texture);
    }

    RSRender_Buffer * RSRender::CreateBuffer(const RSBufferDesc& desc) {
        return g_CurrentRenderer->CreateBuffer(desc);
    }

    void RSRender::DestroyBuffer(RSRender_Buffer* buffer) {
        g_CurrentRenderer->DestroyBuffer(buffer);
    }

    void RSRender::SetShaderResource(RSShaderStage stage, RSShaderResourceView srv) {
        g_CurrentRenderer->SetShaderResource(stage, srv);
    }

    void RSRender::SetShaderSampler(RSShaderStage stage, RSShaderSamplerState sss) {
        g_CurrentRenderer->SetShaderSampler(stage, sss);
    }

    RSRender_Shader* RSRender::CreateShaderFromFile(RSShaderStage stage, const char* fileName) {
        return g_CurrentRenderer->CreateShaderFromFile(stage, fileName);
    }

    RSRender_Shader* RSRender::CreateShaderFromBlob(RSShaderStage stage, void* shaderBlob) {
        return g_CurrentRenderer->CreateShaderFromBlob(stage, shaderBlob);
    }

    void RSRender::DestroyShader(RSRender_Shader* shader) {
        g_CurrentRenderer->DestroyShader(shader);
    }

    void RSRender::SetShader(RSRender_Shader* shader) {
        g_CurrentRenderer->SetShader(shader);
    }

    void RSRender::SetVertexBuffer(RSRender_Buffer* buf) {
        g_CurrentRenderer->SetVertexBuffer(buf);
    }

    void RSRender::SetIndexBuffer(RSRender_Buffer* buf) {
        g_CurrentRenderer->SetIndexBuffer(buf);
    }

    void RSRender::UpdateResolution(bool bIsEditor, float width, float height) {
        g_CurrentRenderer->UpdateResolution(bIsEditor, width, height);
    }

    void RSRender::PresentSwapChain() {
        g_CurrentRenderer->PresentSwapChain();
    }

    void RSRender::Draw(unsigned int vertexCount, RSPrimitiveTopology topology) {
        g_CurrentRenderer->Draw(vertexCount, topology);
    }

    void RSRender::DrawIndexed(unsigned int indexCount, RSPrimitiveTopology topology) {
        g_CurrentRenderer->DrawIndexed(indexCount, topology);
    }

    RSRender* RSRender::getCurrentRenderer() {
        return g_CurrentRenderer;
    }

} // namespace rs
