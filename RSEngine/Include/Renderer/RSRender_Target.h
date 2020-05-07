/*

RSEngine
Copyright (c) 2020 Mason Lee Back

File name: RSRender_Viewport.h

*/

#ifndef _RSRENDER_VIEWPORT_H_
#define _RSRENDER_VIEWPORT_H_

#include <Types\Vector2.h>

namespace rs::Renderer {
	class RSRenderTarget {
	public:
		RSRenderTarget(Vector2 size);
		~RSRenderTarget();

		void Resize(Vector2 size);

		//Camera* camera;

		virtual Vector2 getViewportSize() { return viewportSize; };
		virtual ID3D11Texture2D* getViewportTexture() { return viewportTexture; };
		virtual ID3D11ShaderResourceView* getSRV() { return shaderResourceView; };
		virtual ID3D11DepthStencilView* getDepthStencil() { return depthStencilView; };
		virtual ID3D11RenderTargetView* getRenderTarget() { return renderTargetView; };
		virtual D3D11_VIEWPORT getViewport() { return viewport; };

		D3D11_VIEWPORT viewport;

		Vector2 viewportSize;

		ID3D11ShaderResourceView* shaderResourceView;
		ID3D11Texture2D* viewportTexture;
		ID3D11RenderTargetView* renderTargetView;

		ID3D11Texture2D* depthStencilBuffer;
		ID3D11DepthStencilView* depthStencilView;
	private:
	};
}

#endif // _RSRENDER_VIEWPORT_H_
