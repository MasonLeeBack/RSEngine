/*

RSEngine
Copyright (c) 2019 Mason Lee Back

File name: RSRender_Buffer.cpp

*/

#include <RSEngine.h>

namespace rs::Render {
    RSRender_Buffer::RSRender_Buffer() {
    
    }
    
    RSRender_Buffer::RSRender_Buffer(const RSBufferDesc & desc) {
    
    }
    
    RSRender_Buffer::~RSRender_Buffer() {
    
    }
    
    void RSRender_Buffer::SetBuffer(void * data) {
    
    }
    
    void RSRender_Buffer::UpdateBuffer(void * data) {
    
    }
    
    void* RSRender_Buffer::getBuffer() {
        return buffer;
    }

    RSBufferDesc RSRender_Buffer::getDescription() {
        return description;
    }

} // namespace rs::Render
