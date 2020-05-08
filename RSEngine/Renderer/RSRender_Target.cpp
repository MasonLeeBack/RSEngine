/*

RSEngine
Copyright (c) 2020 Mason Lee Back

File name: RSRender_Target.cpp

*/

#include <Renderer/RSRender.h>

namespace rs {

	namespace Renderer {
		RSRenderTarget::RSRenderTarget(Vector2 size)
		{
			D3D11_TEXTURE2D_DESC textureDesc;

			ZeroMemory(&textureDesc, sizeof(textureDesc));

			textureDesc.Width = static_cast<UINT>(size.X);
			textureDesc.Height = static_cast<UINT>(size.Y);
			textureDesc.MipLevels = 1;
			textureDesc.ArraySize = 1;
			textureDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
			textureDesc.SampleDesc.Count = 1;
			textureDesc.Usage = D3D11_USAGE_DEFAULT;
			textureDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
			textureDesc.CPUAccessFlags = 0;
			textureDesc.MiscFlags = 0;

			g_RSRender->l_Device->CreateTexture2D(&textureDesc, NULL, &viewportTexture);

			D3D11_RENDER_TARGET_VIEW_DESC renderTargetViewDesc;

			renderTargetViewDesc.Format = textureDesc.Format;
			renderTargetViewDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
			renderTargetViewDesc.Texture2D.MipSlice = 0;

			g_RSRender->l_Device->CreateRenderTargetView(viewportTexture, &renderTargetViewDesc, &renderTargetView);

			D3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceViewDesc;

			shaderResourceViewDesc.Format = textureDesc.Format;
			shaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
			shaderResourceViewDesc.Texture2D.MostDetailedMip = 0;
			shaderResourceViewDesc.Texture2D.MipLevels = 1;

			D3D11_TEXTURE2D_DESC DepthStencilDesc;

			DepthStencilDesc.Width = static_cast<UINT>(size.X);
			DepthStencilDesc.Height = static_cast<UINT>(size.Y);
			DepthStencilDesc.MipLevels = 1;
			DepthStencilDesc.ArraySize = 1;
			DepthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
			DepthStencilDesc.SampleDesc.Count = 1;
			DepthStencilDesc.SampleDesc.Quality = 0;
			DepthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
			DepthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
			DepthStencilDesc.CPUAccessFlags = 0;
			DepthStencilDesc.MiscFlags = 0;

			ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

			viewport.TopLeftX = 0;
			viewport.TopLeftY = 0;
			viewport.Height = static_cast<float>(size.X);
			viewport.Width = static_cast<float>(size.Y);
			viewport.MinDepth = 0;
			viewport.MaxDepth = 1;

			viewportSize = Vector2(static_cast<float>(size.X), static_cast<float>(size.Y));

			g_RSRender->l_Device->CreateTexture2D(&DepthStencilDesc, NULL, &depthStencilBuffer);
			g_RSRender->l_Device->CreateDepthStencilView(depthStencilBuffer, NULL, &depthStencilView);

			g_RSRender->l_Device->CreateShaderResourceView(viewportTexture, &shaderResourceViewDesc, &shaderResourceView);
		}

		void RSRenderTarget::Resize(Vector2 size)
		{
			// No need to resize if it's the same size
			if (size == viewportSize)
				return;

			// If the current render target is this texture, we will unreference and restore after reinitializing the target
			ID3D11RenderTargetView* currentRTV;
			ID3D11DepthStencilView* currentDSV;
			g_RSRender->l_DeviceContext->OMGetRenderTargets(1, &currentRTV, &currentDSV);

			bool isCurrentRTV = false;

			if (currentRTV == renderTargetView && currentDSV == depthStencilView)
			{
				g_RSRender->l_DeviceContext->OMSetRenderTargets(1, nullptr, nullptr);
				isCurrentRTV = true;
			}

			renderTargetView->Release();
			shaderResourceView->Release();
			viewportTexture->Release();
			depthStencilBuffer->Release();
			depthStencilView->Release();

			D3D11_TEXTURE2D_DESC textureDesc;

			ZeroMemory(&textureDesc, sizeof(textureDesc));

			textureDesc.Width = static_cast<UINT>(size.X);
			textureDesc.Height = static_cast<UINT>(size.Y);
			textureDesc.MipLevels = 1;
			textureDesc.ArraySize = 1;
			textureDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
			textureDesc.SampleDesc.Count = 1;
			textureDesc.Usage = D3D11_USAGE_DEFAULT;
			textureDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
			textureDesc.CPUAccessFlags = 0;
			textureDesc.MiscFlags = 0;

			g_RSRender->l_Device->CreateTexture2D(&textureDesc, NULL, &viewportTexture);

			D3D11_RENDER_TARGET_VIEW_DESC renderTargetViewDesc;

			renderTargetViewDesc.Format = textureDesc.Format;
			renderTargetViewDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
			renderTargetViewDesc.Texture2D.MipSlice = 0;

			g_RSRender->l_Device->CreateRenderTargetView(viewportTexture, &renderTargetViewDesc, &renderTargetView);

			D3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceViewDesc;

			shaderResourceViewDesc.Format = textureDesc.Format;
			shaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
			shaderResourceViewDesc.Texture2D.MostDetailedMip = 0;
			shaderResourceViewDesc.Texture2D.MipLevels = 1;

			D3D11_TEXTURE2D_DESC DepthStencilDesc;

			DepthStencilDesc.Width = static_cast<UINT>(size.X);
			DepthStencilDesc.Height = static_cast<UINT>(size.Y);
			DepthStencilDesc.MipLevels = 1;
			DepthStencilDesc.ArraySize = 1;
			DepthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
			DepthStencilDesc.SampleDesc.Count = 1;
			DepthStencilDesc.SampleDesc.Quality = 0;
			DepthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
			DepthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
			DepthStencilDesc.CPUAccessFlags = 0;
			DepthStencilDesc.MiscFlags = 0;

			ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

			viewport.TopLeftX = 0;
			viewport.TopLeftY = 0;
			viewport.Height = static_cast<float>(size.Y);
			viewport.Width = static_cast<float>(size.X);
			viewport.MinDepth = 0;
			viewport.MaxDepth = 1;

			viewportSize = Vector2(static_cast<float>(size.X), static_cast<float>(size.Y));

			g_RSRender->l_Device->CreateTexture2D(&DepthStencilDesc, NULL, &depthStencilBuffer);
			g_RSRender->l_Device->CreateDepthStencilView(depthStencilBuffer, NULL, &depthStencilView);

			g_RSRender->l_Device->CreateShaderResourceView(viewportTexture, &shaderResourceViewDesc, &shaderResourceView);

			if (isCurrentRTV) {
				g_RSRender->l_DeviceContext->RSSetViewports(1, &viewport);
				g_RSRender->l_DeviceContext->OMSetRenderTargets(1, &renderTargetView, depthStencilView);
			}
		}

		RSRenderTarget::~RSRenderTarget()
		{
			if (renderTargetView) {
				renderTargetView->Release();
				//delete renderTargetView;
				renderTargetView = NULL;
			}
			if (shaderResourceView) {
				shaderResourceView->Release();
				//delete shaderResourceView;
				shaderResourceView = NULL;
			}
			if (viewportTexture) {
				viewportTexture->Release();
				//delete viewportTexture;
				viewportTexture = NULL;
			}
			if (depthStencilBuffer) {
				depthStencilBuffer->Release();
				//delete depthStencilBuffer;
				depthStencilBuffer = NULL;
			}
			if (depthStencilView) {
				depthStencilView->Release();
				//delete depthStencilView;
				depthStencilView = NULL;
			}
		}
	}
}

