/*

RSEngine
Copyright (c) 2019 Mason Lee Back

File name: RSD3D11.cpp

*/

#include <RSEngine.h>

namespace rs::Render {
    ID3D11Device* g_Device;
    ID3D11DeviceContext* g_DeviceContext;

    IDXGISwapChain* g_SwapChain;

    ID3D11RenderTargetView* g_RenderTarget = nullptr;

    ID3D11Texture2D* g_DepthStencilTexture = nullptr;
    ID3D11DepthStencilView* g_DepthStencil = nullptr;

    bool RSD3D11::Initialize() {
        HRESULT hr;

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

        /* This will be updated if the Editor is enabled or the resolution is changed. */
        SwapChainDesc.BufferDesc = BufferDesc;
        SwapChainDesc.SampleDesc.Count = 1;
        SwapChainDesc.SampleDesc.Quality = 0;
        SwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT | DXGI_USAGE_SHADER_INPUT;
        SwapChainDesc.BufferCount = 1;
        SwapChainDesc.OutputWindow = g_hWnd;
        SwapChainDesc.Windowed = 1;
        SwapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

        hr = D3D11CreateDeviceAndSwapChain(
            NULL, 
            D3D_DRIVER_TYPE_HARDWARE,
            NULL,
            NULL,
            NULL,
            NULL,
            D3D11_SDK_VERSION,
            &SwapChainDesc,
            &g_SwapChain,
            &g_Device,
            NULL,
            &g_DeviceContext
            );
        if (FAILED(hr)) {
            RSThrowError(L"Failed to intialize DirectX.");
            return false;
        }

        /* Set up the viewport for the primary display. */
        D3D11_VIEWPORT viewport;
        ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

        viewport.TopLeftX = 0;
        viewport.TopLeftY = 0;
        viewport.Height = g_resX;
        viewport.Width = g_resY;
        viewport.MinDepth = 0;
        viewport.MaxDepth = 1;

        g_DeviceContext->RSSetViewports(1, &viewport);

        ID3D11Texture2D* BackBuffer;
        hr = g_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&BackBuffer);
        if (FAILED(hr)) {
            RSThrowError(L"Failed to call l_SwapChain->GetBuffer()!");
            return false;
        }

        /* Create a render target view for the backbuffer. */
        hr = g_Device->CreateRenderTargetView(BackBuffer, NULL, &g_RenderTarget);
        if (FAILED(hr)) {
            RSThrowError(L"Failed to call l_Device->CreateRenderTargetView()!");
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

        g_Device->CreateTexture2D(&DepthStencilDesc, NULL, &g_DepthStencilTexture);
        g_Device->CreateDepthStencilView(g_DepthStencilTexture, NULL, &g_DepthStencil);

        g_DeviceContext->OMSetRenderTargets(1, &g_RenderTarget, g_DepthStencil);

        /* Initialize IMGUI. */
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
        ImGui_ImplWin32_Init(g_hWnd);
        ImGui_ImplDX11_Init(g_Device, g_DeviceContext);

        /* Destroy the backbuffer object. */
        BackBuffer->Release();

        return true;
    }

    void RSD3D11::Update() {
        ImGui_ImplDX11_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        /* Update IMGUI subcomponents */
        g_Editor->Update();

        ImGui::Render();
        ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData()); 
    }

    void RSD3D11::Shutdown() {
        g_Device->Release();
        g_DeviceContext->Release();
        g_SwapChain->Release();
        g_DepthStencilTexture->Release();
        g_DepthStencil->Release();
        g_RenderTarget->Release();

        ImGui_ImplDX11_Shutdown();
        ImGui_ImplWin32_Shutdown();
        ImGui::DestroyContext();
    }

    RSRenderTargetView RSD3D11::CreateRenderTarget(RSRender_Texture * texture)
    {
        /* Unimplemented for now */
        return RSRenderTargetView();
    }

    void RSD3D11::ClearRenderTarget(float color[4]) {
        g_DeviceContext->ClearRenderTargetView(g_RenderTarget, color);
    }

    void RSD3D11::ClearDepthStencil() {
        g_DeviceContext->ClearDepthStencilView(g_DepthStencil, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
    }

    RSRender_Texture* RSD3D11::CreateTexture(const RSTextureDesc& desc) {
        RSD3D11_Texture* texture = new RSD3D11_Texture(desc);
        return texture;
    }

    void RSD3D11::DestroyTexture(RSRender_Texture * texture) {
        delete (RSD3D11_Texture*)texture;
        texture = nullptr;
    }

    RSRender_Buffer* RSD3D11::CreateBuffer(const RSBufferDesc& desc) {
        RSD3D11_Buffer* buffer = new RSD3D11_Buffer(desc);
        return buffer;
    }

    void RSD3D11::DestroyBuffer(RSRender_Buffer* buffer) {
        delete (RSD3D11_Buffer*)buffer;
        buffer = nullptr;
    }

    void RSD3D11::SetShaderResource(RSShaderStage stage, RSShaderResourceView srv) {
        switch (stage) {
        case RS_SHADER_STAGE_VS:
            g_DeviceContext->VSSetShaderResources(0, 1, (ID3D11ShaderResourceView* const*)srv);
            break;
        case RS_SHADER_STAGE_DS:
            g_DeviceContext->DSSetShaderResources(0, 1, (ID3D11ShaderResourceView* const*)srv);
            break;
        case RS_SHADER_STAGE_GS:
            g_DeviceContext->GSSetShaderResources(0, 1, (ID3D11ShaderResourceView* const*)srv);
            break;
        case RS_SHADER_STAGE_HS:
            g_DeviceContext->HSSetShaderResources(0, 1, (ID3D11ShaderResourceView* const*)srv);
            break;
        case RS_SHADER_STAGE_PS:
            g_DeviceContext->PSSetShaderResources(0, 1, (ID3D11ShaderResourceView* const*)srv);
            break;
        default:
            break;
        }
    }

    void RSD3D11::SetShaderSampler(RSShaderStage stage, RSShaderSamplerState sss) {
        switch (stage) {

        }
    }

    RSRender_Shader* RSD3D11::CreateShaderFromFile(RSShaderStage stage, const char* fileName) {
        return nullptr;
    }

    RSRender_Shader* RSD3D11::CreateShaderFromBlob(RSShaderStage stage, void* shaderBlob) {
        return nullptr;
    }

    void RSD3D11::DestroyShader(RSRender_Shader* shader) {
    }

    void RSD3D11::SetShader(RSRender_Shader* shader) {
    }

    void RSD3D11::SetVertexBuffer(RSRender_Buffer* buf) {
        RSBufferDesc desc = buf->getDescription();
        if (desc.id == RS_VERTEX_BUFFER) {
            g_DeviceContext->IASetVertexBuffers(0, 1, (ID3D11Buffer* const*)buf->getBuffer(), &desc.uStride, &desc.uOffset);
        }
    }

    void RSD3D11::SetIndexBuffer(RSRender_Buffer* buf) {
        RSBufferDesc desc = buf->getDescription();
        if (desc.id == RS_INDEX_BUFFER) {
            g_DeviceContext->IASetIndexBuffer(((ID3D11Buffer*)buf->getBuffer()), DXGI_FORMAT_R32_UINT, 0);
        }
    }

    void RSD3D11::UpdateResolution(bool bIsEditor, float width, float height) {
    }

    void RSD3D11::PresentSwapChain() {
        g_SwapChain->Present(0, 0);
    }

    void RSD3D11::Draw(unsigned int vertexCount, RSPrimitiveTopology topology) {
        D3D11_PRIMITIVE_TOPOLOGY l_Topology = conv.getTopology(topology);
        g_DeviceContext->IASetPrimitiveTopology(l_Topology);

        g_DeviceContext->Draw(vertexCount, 0);
    }

    void RSD3D11::DrawIndexed(unsigned int indexCount, RSPrimitiveTopology topology) {
        D3D11_PRIMITIVE_TOPOLOGY l_Topology = conv.getTopology(topology);
        g_DeviceContext->IASetPrimitiveTopology(l_Topology);

        g_DeviceContext->DrawIndexed(indexCount, 0, 0);
    }

    ID3D11Device* RSD3D11::getDevice() {
        return g_Device;
    }

    ID3D11DeviceContext* RSD3D11::getDeviceContext() {
        return g_DeviceContext;
    }

} // namespace rs::Render
