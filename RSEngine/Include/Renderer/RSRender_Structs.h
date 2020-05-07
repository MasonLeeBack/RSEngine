/*

RSEngine
Copyright (c) 2020 Mason Lee Back

File name: RSRender_Structs.h

*/

#ifndef _RSRENDER_STRUCTS_H_
#define _RSRENDER_STRUCTS_H_

#include "RSRender_Enums.h"
#include <DirectXMath.h>

#include <Types/RareTypes.h>

namespace rs::Renderer {
	struct RSViewportBackup {
		UINT viewportNum;
		D3D11_VIEWPORT viewport;

		ID3D11RenderTargetView* rtv;
		ID3D11DepthStencilView* dsv;
	};

	struct RSDefaultRenderData {
		Vector3 position;
		Vector3 normal;
		Vector3 tangent;
		Vector2 uv;
	};

	struct RSBufferDesc {
		RSBufferType mType = RSBufferType::BUFFER_TYPE_UNKNOWN;
		RSBufferUsage mUsage = RSBufferUsage::GPU_READ_WRITE;
		unsigned mElementCount = 0;
		unsigned mStride = 0;
		unsigned mStructureByteStride = 0;
	};

	struct RSShaderPipeline {
		RSShaderID shader;
		RSBufferID vertexBuffer;
		RSBufferID indexBuffer;
		RSPrimitiveTopology topology;
		RSRasterID rasterState;
	};

    struct objCB {
        DirectX::XMMATRIX mWorld;
        DirectX::XMMATRIX mView;
        DirectX::XMMATRIX mProjection;
    };

    struct extendedCB {
        DirectX::XMMATRIX mView;
        DirectX::XMMATRIX mProjection;
    };

    struct Light
    {
        Light()
        {
            ZeroMemory(this, sizeof(Light));
        }
        DirectX::XMFLOAT3 dir;
        float pad1;
        DirectX::XMFLOAT3 pos;
        float range;
        DirectX::XMFLOAT3 att;
        float pad2;
        DirectX::XMFLOAT4 ambient;
        DirectX::XMFLOAT4 diffuse;
    };

    struct psCB {
        Light light;
    };

    struct RSTexture {
        bool DrawTexture = false;
        ID3D11Texture2D* TextureSource;
        ID3D11ShaderResourceView* Texture;
        ID3D11SamplerState* SamplerState;
    };
}

#endif // _RSRENDER_STRUCTS_H_
