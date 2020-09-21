/*

RSEngine
Copyright (c) 2020 Mason Lee Back

File name: RSRender_Buffer.cpp

*/

#include <Renderer/RSRender.h>
#include <Core/RSErrorHandling.h>

namespace rs::Renderer {
    RSRender_Buffer::RSRender_Buffer(const RSBufferDesc& desc)
        : mDesc(desc), mDirty(true), mpCPUData(nullptr), mpGPUData(nullptr)
    {}

    RSRender_Buffer::~RSRender_Buffer()
    {
    }

    void RSRender_Buffer::Initialize(const void* pData)
    {
        D3D11_BUFFER_DESC bufDesc;
        bufDesc.Usage = static_cast<D3D11_USAGE>(mDesc.mUsage);
        bufDesc.BindFlags = static_cast<D3D11_BIND_FLAG>(mDesc.mType);
        bufDesc.ByteWidth = mDesc.mStride * mDesc.mElementCount;
        bufDesc.CPUAccessFlags = mDesc.mUsage == RSBufferUsage::GPU_READ_CPU_WRITE ? D3D11_CPU_ACCESS_WRITE : 0;
        bufDesc.MiscFlags = 0;
        bufDesc.StructureByteStride = mDesc.mStructureByteStride;

        D3D11_SUBRESOURCE_DATA* pBufData = nullptr;
        D3D11_SUBRESOURCE_DATA bufData = {};
        if (pData)
        {
            bufData.pSysMem = pData;
            bufData.SysMemPitch = 0;
            bufData.SysMemSlicePitch = 0;
            pBufData = &bufData;

           // mpCPUData = malloc(bufDesc.ByteWidth);
            //memcpy(mpCPUData, pData, bufDesc.ByteWidth);
        }
        else
        {
            int a = 5;
        }

        int hr = g_RSRender->l_Device->CreateBuffer(&bufDesc, pBufData, &this->mpGPUData);
        if (FAILED(hr))
        {
            RSHandleError("Failed to create buffer");
        }
    }

    void RSRender_Buffer::CleanUp()
    {
        if (mpGPUData)
        {
            mpGPUData->Release();
            mpGPUData = nullptr;
        }

        if (mpCPUData)
        {
            free(mpCPUData);
        }
    }

    void RSRender_Buffer::Update(const void* pData)
    {
        auto* ctx = g_RSRender->l_DeviceContext;

        D3D11_MAPPED_SUBRESOURCE mappedResource = {};
        constexpr UINT Subresource = 0;
        constexpr UINT MapFlags = 0;
        const UINT Size = mDesc.mStride * mDesc.mElementCount;

        ctx->Map(mpGPUData, Subresource, D3D11_MAP_WRITE_DISCARD, MapFlags, &mappedResource);
        memcpy(mappedResource.pData, pData, Size);
        ctx->Unmap(mpGPUData, Subresource);
    }

} // namespace rs::Renderer
