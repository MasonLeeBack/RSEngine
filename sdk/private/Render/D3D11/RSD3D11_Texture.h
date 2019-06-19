/*

RSEngine
Copyright (c) 2019 Mason Lee Back

File name: RSD3D11_Texture.h

*/

#ifndef _RSD3D11_Texture_h_
#define _RSD3D11_Texture_h_

namespace rs::Render {
    class RSD3D11_Texture : public RSRender_Texture {
    public:
        RSD3D11_Texture();
        RSD3D11_Texture(const RSTextureDesc& desc);
        ~RSD3D11_Texture();

        void updateTexture(void* data) override;

        RSShaderResourceView* getShaderResourceView() override;
        RSShaderSamplerState* getShaderSamplerState() override;

    private:
        RSTexture2D* tex = nullptr;
        RSShaderResourceView* srv = nullptr;
        RSShaderSamplerState* samp = nullptr;
    };

} // namespace rs::Render

#endif // _RSD3D11_Texture_h_
