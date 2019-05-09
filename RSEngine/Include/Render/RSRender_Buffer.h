/*

RSEngine
Copyright (c) 2019 Mason Lee Back

File name: RSRender_Buffer.h

*/

#pragma once
#ifndef _RSRender_Buffer_h_
#define _RSRender_Buffer_h_

namespace rs::Render {
    class RSRender_Buffer {
    public:
        RSRender_Buffer();
        RSRender_Buffer(const RSBufferDesc& desc);
        ~RSRender_Buffer();

        void SetBuffer(void* data);
        void UpdateBuffer(void* data);

        void* getBuffer();
        RSBufferDesc getDescription();
    protected:
        RSBufferDesc description;
        void* buffer;
    };

} // namespace rs::Render

#endif // _RSRender_Buffer_h_
