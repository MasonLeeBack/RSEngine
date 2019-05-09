/*

RSEngine
Copyright (c) 2019 Mason Lee Back

File name: RSD3D11_Texture.cpp

*/

#include <RSEngine.h>

namespace rs::Render {
    RSD3D11_Texture::RSD3D11_Texture() : tex(nullptr), srv(nullptr), samp(nullptr) {

    }

    RSD3D11_Texture::RSD3D11_Texture(const RSTextureDesc& desc) : tex(nullptr), srv(nullptr), samp(nullptr) {
    
    }

    RSD3D11_Texture::~RSD3D11_Texture() {
    
    }

    void RSD3D11_Texture::updateTexture(void* data) {
    
    }

    RSShaderResourceView* RSD3D11_Texture::getShaderResourceView() {
        return srv;
    }

    RSShaderSamplerState* RSD3D11_Texture::getShaderSamplerState() {
        return samp;
    }

} // namespace rs::Render
