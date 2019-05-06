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

#include <Render/ImGui/imgui.h>
#include <Render/ImGui/imgui_impl_win32.h>
#include <Render/ImGui/imgui_impl_dx11.h>

namespace rs {
    struct objCB {
        DirectX::XMMATRIX  WVP;
        bool objectTextured = false;
    };

    struct cameraMatrix {
        DirectX::XMMATRIX viewMatrix;
        DirectX::XMMATRIX projMatrix;
    };

    enum rasterType {
        RT_NORMAL,
        RT_WIREFRAME
    };

    extern cameraMatrix     g_cameraMatrix;

    typedef std::map<const char*, ID3D11VertexShader*>  VERTEXSHADER_MAP;
    typedef std::map<const char*, ID3D11PixelShader*>   PIXELSHADER_MAP;
    typedef std::map<const char*, ID3D11InputLayout*>   INPUTLAYOUT_MAP;

    extern VERTEXSHADER_MAP VertexMap;
    extern PIXELSHADER_MAP  PixelMap;
    extern INPUTLAYOUT_MAP  LayoutMap;

    extern objCB constantBuffer;

    typedef enum SHADER_TYPE {
        ST_PixelShader,
        ST_VertexShader
    }ShaderType;

    class Render {
    public:
        bool Initialize();
        bool UpdateSwapChainResolution();
        void Shutdown();
        void RenderScene();

        void RenderToEditor();
        void RenderToWindow();

        void* GetRenderedTexture(); // Valid only if RenderToEditor is called;

        void UpdateViewportSize(float resX, float resY);

        bool LoadShader(SHADER_TYPE shaderType, RenderPipeline* pipeline, const char* filename);

    private:
        void UpdateCamera();
        bool LoadTexture(RSTexture* texture, const char* filename);
    };

    extern IDXGISwapChain*           pdx_SwapChain;
    extern ID3D11Device*             pdx_Device;
    extern ID3D11DeviceContext*      pdx_DeviceContext;
    extern ID3D11RenderTargetView*   pdx_RenderTargetView;

    extern ID3D11Buffer*             pdx_ConstantBuffer;

    extern ID3D11RasterizerState*    pdx_RasterizerState;

    extern ID3D11DepthStencilView*   pdx_DepthStencilView;
    extern ID3D11Texture2D*          pdx_DepthStencilBuffer;

    extern ID3D11ShaderResourceView* pdx_EditorViewportSRV;

    extern Render* g_Renderer;

} // namespace rs

#ifdef _USE_FBX_SDK_
#include "LoadModel_FBX.h"
#endif // _USE_FBX_SDK_

#include "stb_image.h"

#include "LoadModel_OBJ.h"

#include "RSGeometryGenerator.h"

#endif // _RSRender_h_
