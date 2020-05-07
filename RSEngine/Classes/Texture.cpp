/*

RSEngine
Copyright (c) 2019 Mason Lee Back

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

File name: Texture.cpp

*/

#include <Classes/Texture.h>
#include <Renderer/RSRender.h>
#include <Renderer/stb_image.h>

namespace rs {
    INITIALIZE_INSTANCE_SOURCE(Texture);

    void Texture::render() {
        HRESULT hr;
        RSTexture* tex = &Parent->pipeline->Texture;

        if (tex->DrawTexture == false) {

            // load the texture data and assign the texture file
            int tex_width, tex_height, tex_bpp;
            unsigned char *data = stbi_load(File.c_str(), &tex_width, &tex_height, &tex_bpp, STBI_rgb_alpha);
            if (data == NULL)
                return;

            // assign the subresource data
            D3D11_SUBRESOURCE_DATA mData;
            mData.pSysMem = data;
            mData.SysMemPitch = tex_width * tex_bpp;
            mData.SysMemSlicePitch = 0;

            // set the texture description and create the texture resource
            D3D11_TEXTURE2D_DESC l_textureDesc;
            ZeroMemory(&l_textureDesc, sizeof(D3D11_TEXTURE2D_DESC));
            l_textureDesc.Width = tex_width;
            l_textureDesc.Height = tex_height;
            l_textureDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
            l_textureDesc.MipLevels = 1;
            l_textureDesc.ArraySize = 1;
            l_textureDesc.SampleDesc.Count = 1;
            l_textureDesc.Usage = D3D11_USAGE_DEFAULT;
            l_textureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;
            hr = g_RSRender->l_Device->CreateTexture2D(&l_textureDesc, &mData, &tex->TextureSource);
            if (FAILED(hr))
                return;

            // create shader resource view description and then create the view
            D3D11_SHADER_RESOURCE_VIEW_DESC l_srvDesc;
            l_srvDesc.Format = l_textureDesc.Format;
            l_srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
            l_srvDesc.Texture2D.MostDetailedMip = 0;
            l_srvDesc.Texture2D.MipLevels = 1;
            hr = g_RSRender->l_Device->CreateShaderResourceView(tex->TextureSource, &l_srvDesc, &tex->Texture);
            if (FAILED(hr))
                return;

            // create sampler description and then the sampler state
            D3D11_SAMPLER_DESC samplerDesc;
            samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
            samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
            samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
            samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
            samplerDesc.MipLODBias = 0.0f;
            samplerDesc.MaxAnisotropy = 1;
            samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
            samplerDesc.BorderColor[0] = 0;
            samplerDesc.BorderColor[1] = 0;
            samplerDesc.BorderColor[2] = 0;
            samplerDesc.BorderColor[3] = 0;
            samplerDesc.MinLOD = 0;
            samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;
            hr = g_RSRender->l_Device->CreateSamplerState(&samplerDesc, &tex->SamplerState);
            if (FAILED(hr))
                return;

            tex->DrawTexture = true;
        }

        renderChildren();
    }

} // namespace RS

