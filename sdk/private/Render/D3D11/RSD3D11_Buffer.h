/*

RSEngine
Copyright (c) 2019 Mason Lee Back

File name: RSD3D11_Buffer.h

*/

#pragma once
#ifndef _RSD3D11_Buffer_h_
#define _RSD3D11_Buffer_h_

namespace rs::Render {
    class RSD3D11_Buffer : public RSRender_Buffer {
    public:
        RSD3D11_Buffer();
        RSD3D11_Buffer(const RSBufferDesc& desc);
        ~RSD3D11_Buffer();

        void SetBuffer(void* data) override;
        void UpdateBuffer(void* data) override;
            
        void* getBuffer() override;
        RSBufferDesc getDescription() override;

    protected:
        RSBufferDesc description;
        ID3D11Buffer* l_Buffer;
        
        ID3D11Device* l_RenderDevice;
    };

} // namespace rs::Render

#endif // _RSD3D11_Buffer_h_
