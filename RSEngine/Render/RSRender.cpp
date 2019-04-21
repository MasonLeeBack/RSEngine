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

#include <RSEngine.h>

using namespace DirectX;

namespace rs {
    IDXGISwapChain*             pdx_SwapChain;
    ID3D11Device*               pdx_Device;
    ID3D11DeviceContext*        pdx_DeviceContext;
    ID3D11RenderTargetView*     pdx_RenderTargetView;

    ID3D11Buffer*               pdx_ConstantBuffer; // shared for now

    ID3D11RasterizerState*      pdx_RasterizerState;

    ID3D11DepthStencilView*     pdx_DepthStencilView;
    ID3D11Texture2D*            pdx_DepthStencilBuffer;

    Render*                     g_Renderer;

    objCB                       constantBuffer;

    cameraMatrix                g_cameraMatrix;

    std::vector<RenderPipeline*> pipelines;

    bool Render::Initialize() {
        HRESULT hr;

        // Enumerate available DX11 adapters
        IDXGIFactory* pFactory = NULL;
        CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&pFactory);

        IDXGIAdapter* pAdapter;
        std::vector <IDXGIAdapter*> vAdapters;
        UINT i = 0;
        while (pFactory->EnumAdapters(i, &pAdapter) != DXGI_ERROR_NOT_FOUND) {
            vAdapters.push_back(pAdapter);
            ++i;
        }

        // Figure out DirectX feature levels
        const D3D_FEATURE_LEVEL FeatureLevels[] {
            D3D_FEATURE_LEVEL_11_0,
            D3D_FEATURE_LEVEL_11_1
        };

        DXGI_MODE_DESC BufferDesc;
        ZeroMemory(&BufferDesc, sizeof(DXGI_MODE_DESC));

        BufferDesc.Width = g_resX;
        BufferDesc.Height = g_resY;
        BufferDesc.RefreshRate.Numerator = 60;
        BufferDesc.RefreshRate.Denominator = 1;
        BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
        BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;


        DXGI_SWAP_CHAIN_DESC SwapChainDesc;
        ZeroMemory(&SwapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC));

        // Updated by Render::UpdateSwapChainResolution
        SwapChainDesc.BufferDesc = BufferDesc;
        SwapChainDesc.SampleDesc.Count = 1;
        SwapChainDesc.SampleDesc.Quality = 0;
        SwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        SwapChainDesc.BufferCount = 1;
        SwapChainDesc.OutputWindow = g_hWnd;
        SwapChainDesc.Windowed = 1; // Engine settings will change this (as well as UpdateSwapChainResolution)
        SwapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;


        // Create the device.
        hr = D3D11CreateDeviceAndSwapChain(
            NULL, // Use the PADAPTER enumeration later when we introduce settings
            D3D_DRIVER_TYPE_HARDWARE,
            NULL,
            NULL,
            NULL, // Feature levels is ready for use, however we're keeping things simple for now
            NULL,
            D3D11_SDK_VERSION,
            &SwapChainDesc,
            &pdx_SwapChain,
            &pdx_Device,
            NULL,
            &pdx_DeviceContext
        );
        if (FAILED(hr)) {
            RSThrowError(L"DirectX 11 failed to initialize.");
            return false;
        }

        // Set up the viewport
        D3D11_VIEWPORT viewport;
        ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

        viewport.TopLeftX = 0;
        viewport.TopLeftY = 0;
        viewport.Height = static_cast<float>(g_resY);
        viewport.Width = static_cast<float>(g_resX);
        viewport.MinDepth = 0;
        viewport.MaxDepth = 1;

        pdx_DeviceContext->RSSetViewports(1, &viewport);

        ID3D11Texture2D* BackBuffer;
        hr = pdx_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&BackBuffer);
        if (FAILED(hr)) {
            RSThrowError(L"Failed to get the backbuffer.");
            return false;
        }

        // BackBuffer Render Target
        hr = pdx_Device->CreateRenderTargetView(BackBuffer, NULL, &pdx_RenderTargetView);
        if (FAILED(hr)) {
            RSThrowError(L"Could not create backbuffer render target.");
            return false;
        }

        D3D11_BUFFER_DESC cbbd;
        ZeroMemory(&cbbd, sizeof(D3D11_BUFFER_DESC));

        cbbd.Usage = D3D11_USAGE_DEFAULT;
        cbbd.ByteWidth = sizeof(objCB);
        cbbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
        cbbd.CPUAccessFlags = 0;
        cbbd.MiscFlags = 0;

        hr = pdx_Device->CreateBuffer(&cbbd, NULL, &pdx_ConstantBuffer);
        if (FAILED(hr)) {
            RSThrowError(L"Failed to create constant buffer.");
            return false;
        }

        D3D11_TEXTURE2D_DESC DepthStencilDesc;

        DepthStencilDesc.Width = g_resX;
        DepthStencilDesc.Height = g_resY;
        DepthStencilDesc.MipLevels = 1;
        DepthStencilDesc.ArraySize = 1;
        DepthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
        DepthStencilDesc.SampleDesc.Count = 1;
        DepthStencilDesc.SampleDesc.Quality = 0;
        DepthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
        DepthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
        DepthStencilDesc.CPUAccessFlags = 0;
        DepthStencilDesc.MiscFlags = 0;

        pdx_Device->CreateTexture2D(&DepthStencilDesc, NULL, &pdx_DepthStencilBuffer);
        pdx_Device->CreateDepthStencilView(pdx_DepthStencilBuffer, NULL, &pdx_DepthStencilView);

        pdx_DeviceContext->OMSetRenderTargets(1, &pdx_RenderTargetView, pdx_DepthStencilView);

        // Clean up
        BackBuffer->Release();
        pFactory->Release();
        vAdapters.clear();

        /*D3D11_RASTERIZER_DESC wfdesc;
        ZeroMemory(&wfdesc, sizeof(D3D11_RASTERIZER_DESC));
        wfdesc.FillMode = D3D11_FILL_WIREFRAME;
        wfdesc.CullMode = D3D11_CULL_NONE;
        hr = pdx_Device->CreateRasterizerState(&wfdesc, &pdx_RasterizerState);

        pdx_DeviceContext->RSSetState(pdx_RasterizerState);*/

        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
        ImGui_ImplWin32_Init(g_hWnd);
        ImGui_ImplDX11_Init(pdx_Device, pdx_DeviceContext);

        return true;
    }

    bool Render::UpdateSwapChainResolution() {
        int newWidth = 0, newHeight = 0;
        pdx_SwapChain->ResizeBuffers(0, newWidth, newHeight, DXGI_FORMAT_UNKNOWN, NULL);
        return false;
    }

    void Render::Shutdown() {
        pdx_Device->Release();
        pdx_DeviceContext->Release();
        pdx_SwapChain->Release();
        pdx_RenderTargetView->Release();
        pdx_ConstantBuffer->Release();
        pdx_DepthStencilBuffer->Release();
        pdx_DepthStencilView->Release();
        //pdx_RasterizerState->Release();

        for (auto pipeline : pipelines) {
            pipeline->IndexBuffer->Release();
            pipeline->InputLayout->Release();
            pipeline->PixelShader->Release();
            pipeline->VertexBuffer->Release();
            pipeline->VertexBuffer->Release();
            pipeline->VertexShader->Release();
        }

        // And any subcomponents of the renderer...
        ImGui_ImplDX11_Shutdown();
        ImGui_ImplWin32_Shutdown();
        ImGui::DestroyContext();

    }

    void Render::RenderScene() {
        float rgba[4] = { 0.1f, 0.1f, 0.1f, 0.0f };

        pdx_DeviceContext->ClearRenderTargetView(pdx_RenderTargetView, rgba);
        pdx_DeviceContext->ClearDepthStencilView(pdx_DepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

        UpdateCamera();
        RenderInstance(eng);
        RenderAllPipelines();

        ImGui_ImplDX11_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        // If any ImGui subcomponents (i.e. Editor) need to be updated,
        // now is the time to do so.
        g_Editor->Update();

        ImGui::Render();
        ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
        
        pdx_SwapChain->Present(0, 0);
    }

    void Render::UpdateCamera() {
#ifndef _EDITOR
        // Camera objects should only be at the root directory.
        // Ignore them if they're anywhere else.
        for (auto kid : eng->GetChildren())
        {
            if (kid->ClassName == "Camera")
            {
                std::shared_ptr<Camera> cam = std::static_pointer_cast<Camera>(kid);

                cam->ViewportSize = Vector2(static_cast<float>(g_resX), static_cast<float>(g_resY));
            }
        }
        static XMVECTOR eyePos = XMVectorSet(0.0f, 0.0f, -2.0f, 0.0f);
        XMFLOAT3 eyePosFloat3;
        XMStoreFloat3(&eyePosFloat3, eyePos);
        eyePosFloat3.y += 0.0001f;
        eyePosFloat3.x -= 0.0001f;
        eyePos = XMLoadFloat3(&eyePosFloat3);
        XMVECTOR lookAtPos = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
        XMVECTOR upVector = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

        g_cameraMatrix.viewMatrix = XMMatrixLookAtLH(eyePos, lookAtPos, upVector);
        g_cameraMatrix.projMatrix = XMMatrixPerspectiveFovLH(XMConvertToRadians(90.0f), (static_cast<float>(g_resX) / static_cast<float>(g_resY)), 0.1f, 1000.0f);
#else // _EDITOR

#endif // _EDITOR
    }

    void Render::RenderAllPipelines() {
        for (auto pipeline : pipelines) {
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

            if (!pipeline->IndexBuffer)
                pdx_DeviceContext->Draw(pipeline->VertexCount, 0);
            else
                pdx_DeviceContext->IASetIndexBuffer(pipeline->IndexBuffer, DXGI_FORMAT_R32_UINT, 0);
                pdx_DeviceContext->DrawIndexed(pipeline->IndexCount, 0, 0);

        }
    }

} // namespace rs
