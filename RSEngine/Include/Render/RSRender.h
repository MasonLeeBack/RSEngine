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

File name: RSRender.h

*/

#pragma once
#ifndef _RSRender_h_
#define _RSRender_h_

#include <Render/ThirdParty/ImGui/imgui.h>
#include <Render/ThirdParty/ImGui/imgui_impl_win32.h>
#include <Render/ThirdParty/ImGui/imgui_impl_dx11.h>

#include <Render/ThirdParty/stb_image.h>

#include "RSRender_Types.h"
#include "RSRender_Math.h"
#include "RSRender_Buffer.h"
#include "RSRender_Shader.h"
#include "RSRender_Texture.h"
#include "RSRender_EditorView.h"

namespace rs::Render {

    typedef std::map<const char*, RSRender_Shader*> RSShaderMap;
    extern RSShaderMap shaderMap;

    class RSRender {
    public:
        virtual bool Initialize();
        virtual void Update();
        virtual void Shutdown();

        virtual RSRenderTargetView CreateRenderTarget(RSRender_Texture* texture);
        virtual void ClearRenderTarget(float color[4]);

        virtual void ClearDepthStencil();

        virtual RSRender_Texture* CreateTexture(const RSTextureDesc& desc);
        virtual void DestroyTexture(RSRender_Texture* texture);

        virtual RSRender_Buffer* CreateBuffer(const RSBufferDesc& desc);
        virtual void DestroyBuffer(RSRender_Buffer* buffer);

        virtual void SetShaderResource(RSShaderStage stage, RSShaderResourceView srv);
        virtual void SetShaderSampler(RSShaderStage stage, RSShaderSamplerState sss);

        virtual RSRender_Shader* CreateShaderFromFile(RSShaderStage stage, const char* fileName);
        virtual RSRender_Shader* CreateShaderFromBlob(RSShaderStage stage, void* shaderBlob);
        virtual void DestroyShader(RSRender_Shader* shader);

        virtual void SetShader(RSRender_Shader* shader);

        virtual void SetVertexBuffer(RSRender_Buffer* buf);
        virtual void SetIndexBuffer(RSRender_Buffer* buf);

        virtual void UpdateResolution(bool bIsEditor, float width, float height);

        virtual void PresentSwapChain();

        virtual void Draw(unsigned int vertexCount, RSPrimitiveTopology topology);
        virtual void DrawIndexed(unsigned int indexCount, RSPrimitiveTopology topology);

        virtual RSRender* getCurrentRenderer();

    };

    extern RSRender* g_Renderer;

} // namespace rs::Render

#ifdef _WIN32
#include <Render/D3D11/RSD3D11.h>
#endif

#endif // _RSRender_h_
