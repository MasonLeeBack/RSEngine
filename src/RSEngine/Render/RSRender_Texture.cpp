/*

RSEngine
Copyright (c) 2019 Mason Lee Back

File name: RSRender_Texture.cpp

*/

#include <Render/RSRender.h>

namespace rs::Render {
    RSRender_Texture::RSRender_Texture() : tex(nullptr), srv(nullptr), samp(nullptr) {

    }

    RSRender_Texture::RSRender_Texture(const RSTextureDesc & desc) : tex(nullptr), srv(nullptr), samp(nullptr) {

    }

    RSRender_Texture::~RSRender_Texture() {

    }

    void RSRender_Texture::updateTexture(void* data) {

    }

    RSShaderResourceView* RSRender_Texture::getShaderResourceView() {
        
        if (srv == nullptr) {
            return nullptr;
        }
        return srv;
    }

    RSShaderSamplerState* RSRender_Texture::getShaderSamplerState() {
        return samp;
    }

} // namespace rs::Render
