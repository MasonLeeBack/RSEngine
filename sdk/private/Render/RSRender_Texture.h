/*

RSEngine
Copyright (c) 2019 Mason Lee Back

File name: RSRender_Texture.h

*/

#ifndef _RSRender_Texture_h_
#define _RSRender_Texture_h_

namespace rs::Render {
    class RSRender_Texture {
    public:
        RSRender_Texture();
        RSRender_Texture(const RSTextureDesc& desc);
        ~RSRender_Texture();

        virtual void updateTexture(void* data);

        virtual RSShaderResourceView* getShaderResourceView();
        virtual RSShaderSamplerState* getShaderSamplerState();

    private:
        RSTexture2D* tex = nullptr;
        RSShaderResourceView* srv = nullptr;
        RSShaderSamplerState* samp = nullptr;
    };

} // namespace rs::Render

#endif // _RSRender_Texture_h_
