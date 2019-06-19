/*

RSEngine
Copyright (c) 2019 Mason Lee Back

File name: RSD3D11_Buffer.cpp

*/

#include <Render/D3D11/RSD3D11.h>

#ifdef _WIN32

namespace rs::Render {
    RSD3D11_Buffer::RSD3D11_Buffer() : l_Buffer(nullptr) {}
    RSD3D11_Buffer::RSD3D11_Buffer(const RSBufferDesc& desc) : description(desc) {
        /* Get D3D11 renderer */
        l_RenderDevice = ((RSD3D11*)g_Renderer->getCurrentRenderer())->getDevice();
    }

    RSD3D11_Buffer::~RSD3D11_Buffer() {
        if (l_Buffer)
            l_Buffer->Release();
    }

    void RSD3D11_Buffer::SetBuffer(void* data) {
        if (description.id == RS_UNSET_BUFFER)
            return;

        if (buffer != nullptr) {
            UpdateBuffer(data);
            return;
        }

        D3D11_BUFFER_DESC bufferDesc;
        ZeroMemory(&bufferDesc, sizeof(D3D11_BUFFER_DESC));
        bufferDesc.BindFlags = description.id;
        bufferDesc.Usage = D3D11_USAGE_DEFAULT;
        bufferDesc.ByteWidth = description.uByteWidth;
        bufferDesc.CPUAccessFlags = 0;

        D3D11_SUBRESOURCE_DATA subData;
        ZeroMemory(&subData, sizeof(D3D11_SUBRESOURCE_DATA));
        subData.pSysMem = data;

        /* Create the buffer. */
        l_RenderDevice->CreateBuffer(&bufferDesc, &subData, &l_Buffer);
    }

    void RSD3D11_Buffer::UpdateBuffer(void* data) {

    }

    void* RSD3D11_Buffer::getBuffer() {
        return l_Buffer;
    }

    RSBufferDesc RSD3D11_Buffer::getDescription() {
        return description;
    }

} // namespace rs::Render

#endif // _WIN32
