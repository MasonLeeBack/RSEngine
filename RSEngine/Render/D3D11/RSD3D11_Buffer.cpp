/*

RSEngine
Copyright (c) 2019 Mason Lee Back

File name: RSD3D11_Buffer.cpp

*/

#include <RSEngine.h>

namespace rs::Render {
    RSD3D11_Buffer::RSD3D11_Buffer() : buffer(nullptr) {}
    RSD3D11_Buffer::RSD3D11_Buffer(const RSBufferDesc& desc) : description(desc) {
        /* Get D3D11 renderer */
        l_RenderDevice = ((RSD3D11*)g_Renderer->getCurrentRenderer())->getDevice();
    }

    RSD3D11_Buffer::~RSD3D11_Buffer() {
        if ((ID3D11Buffer*)buffer)
            ((ID3D11Buffer*)buffer)->Release();
    }

    void RSD3D11_Buffer::SetBuffer(void* data) {
        if (description.id == RS_UNSET_BUFFER)
            return;

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
        ID3D11Buffer* tempBuf;
        l_RenderDevice->CreateBuffer(&bufferDesc, &subData, &tempBuf);

        /* Assign the buffer to the private data object. */
        buffer = tempBuf;
    }

    void RSD3D11_Buffer::UpdateBuffer(void* data) {

    }

} // namespace rs::Render
