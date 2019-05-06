/*

RSEngine
Copyright (c) 2019 Mason Lee Back

File name: RSRenderTypes.h

*/

#ifndef _RSRenderTypes_h_
#define _RSRenderTypes_h_

#include "RSRenderMath.h"

namespace rs {
    struct RSTexture {
        bool                        DrawTexture = false;
        ID3D11Texture2D*            TextureSource;
        ID3D11ShaderResourceView*   Texture;
        ID3D11SamplerState*         SamplerState;
    };

    struct RenderPipeline {
        ID3D11VertexShader* VertexShader;
        ID3D11InputLayout*  InputLayout;
        ID3D11PixelShader*  PixelShader;

        ID3D11Buffer*       VertexBuffer;
        ID3D11Buffer*       IndexBuffer;

        DirectX::XMMATRIX   ViewMatrix;

        RSTexture           Texture;

        int                 VertexCount;
        int                 IndexCount;
    };
}

#endif
