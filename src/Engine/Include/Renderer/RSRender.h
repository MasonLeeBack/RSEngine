/*

RSEngine
Copyright (c) 2019 Mason Lee Back

File name: RSRender.h

*/

#ifndef _RSRENDER_H_
#define _RSRENDER_H_

struct ID3D11Device;
struct ID3D11DeviceContext;
struct ID3D11RenderTargetView;
struct ID3D11DepthStencilView;

namespace rs {
	class RSEngine;
	class Vector2;
	class Vector3;
}

#include <Types/RSArray.h>

#include "RSRender_Enums.h"
#include "RSRender_Structs.h"
#include "RSRender_Target.h"
#include "RSRender_Buffer.h"
#include "RSRender_Texture.h"
#include "RSRender_Camera.h"
#include "RSRender_Shader.h"
#include "RSRender_Pipeline.h"

namespace rs::Renderer {

	const unsigned int BUFFER_COUNT = 3;

	class RenderClass {
	public:
		RenderClass(RSEngine* engine);
		~RenderClass();

		bool Initialize();
		bool InitD3D11();
		void Shutdown();

		void DrawScene();

		void UpdateSwapChainResolution(Vector2);

		Vector2 GetViewportSize();

		Vector2 getWindowResolution();

		void EnableEditorRenderTarget(bool, RSRenderTarget*);
		void SetRenderTarget(RSRenderTarget*);
		void SetMultipleRenderTargets(RSRenderTarget*, int = 1);
		void SetDefaultRenderTarget();

		void ClearRenderTargetDefault();
		void ClearRenderTarget(float[4], float, uint8_t);

		void AssignShader(RSRender_Shader*);

		void UpdateCamera(RSRender_Camera);
		virtual RSRender_Buffer* getCameraBuffer() { return cameraConstBuf; };

		void SetCullState(RSCullState cullState);

		void SetTransparency(float alpha);
		void AddToAlphaPass(RSRenderPipeline* pipeline);

		// DirectX 11 specific
		ID3D11Device* l_Device;
		ID3D11DeviceContext* l_DeviceContext;

		ID3D11RenderTargetView* currentRTV;
		ID3D11DepthStencilView* currentDSV;
	private:

		bool CreateDefaultRenderTargetView();
		bool CreateDepthStencilView();

		void CreateViewport();

		void BindFirstPass();
		void BindLastPass();

		RSRender_Buffer* cameraConstBuf;
		cameraConst cb_Camera;

		RSEngine* l_pEngine;

		// Private DX11
		IDXGISwapChain* l_SwapChain;
		D3D11_VIEWPORT viewport;
		Vector2 viewportSize;

		// Rasterizer states -
		// These are set using SetCullState and are called by
		// the pipeline.
		ID3D11RasterizerState* cullAllRasterizerState;
		ID3D11RasterizerState* cullNoneRasterizerState;

		// Default screen render target / depth stencil
		ID3D11RenderTargetView* renderTargetView;
		ID3D11Texture2D* depthStencilBuffer;
		ID3D11DepthStencilView* depthStencilView;

		// Deferred rendering pipeline
		bool RenderDeffered;
		RSRenderTarget* graphicsBuffer[BUFFER_COUNT];
		RSRenderPipeline* screenQuadPipeline = nullptr;

		void InitDefferedRenderingBuffer();
		void DestroyDefferedRenderingBuffer();

		void InitScreenQuad();

		// Editor render target
		// Only used if the editor is initialized at
		// startup or is able to be initialized during the GameLoop
		bool RenderToEditor = false;
		RSRenderTarget* editorRT;

		// Alpha stuff
		RSArray<RSRenderPipeline*> alphaPasses;
		void renderAlphaPass();
	
		// Blend states - 
		// I don't have any documentation on this yet.
		ID3D11BlendState* transparencyBlendState;
		ID3D11BlendState* guiTransparencyBlendState;
		void InitializeBlendStates();
	};

	////LEGACY LEGACY LEGACY////
	extern Vector2 renderResolution;
	extern bool g_Fullscreen;

	extern RenderClass* g_RSRender;

}

#endif // _RSRENDER_H_
