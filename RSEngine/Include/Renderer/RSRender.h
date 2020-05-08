/*

RSEngine
Copyright (c) 2019 Mason Lee Back

File name: RSRender.h

*/

#ifndef _RSRENDER_H_
#define _RSRENDER_H_

#include <assert.h>
#include <vector>
#include <map>

#include <Windows.h>
#include <d3d11.h>
#include <DirectXMath.h>

#include <ThirdParty/ImGui/imgui.h>
#include <ThirdParty/ImGui/imgui_impl_win32.h>
#include <ThirdParty/ImGui/imgui_impl_dx11.h>

#define RSThrowError(x) MessageBox(NULL, x, L"Error!", MB_OK);

#include <Types/Vector2.h>
#include <Types/Vector3.h>
#include <Window/WindowSystem.h>

#include <Editor/Editor.h>

#include "RSRender_Enums.h"
#include "RSRender_Structs.h"
#include "RSRender_Target.h"
#include "RSRender_Buffer.h"
#include "RSRender_Camera.h"
#include "RSRender_Shader.h"
#include "RSRender_Pipeline.h"

namespace rs::Renderer {

	typedef std::map<RSPipelineID, RSShaderPipeline*> pipeline_map;

	const UINT BUFFER_COUNT = 3;

	class RenderClass {
	public:
		RenderClass();
		~RenderClass();

		bool Initialize();
		bool InitD3D11();
		void Shutdown();

		void DrawScene();

		void UpdateSwapChainResolution(Vector2);

		void EnableEditorRenderTarget(bool, RSRenderTarget*);
		void SetRenderTarget(RSRenderTarget*);
		void RenderClass::SetMultipleRenderTargets(RSRenderTarget*, int = 1);
		void SetDefaultRenderTarget();

		void ClearRenderTargetDefault();
		void ClearRenderTarget(float[4], float, uint8_t);

		void AssignShader(RSRender_Shader*);

		void UpdateCamera(RSRender_Camera);
		virtual RSRender_Buffer* getCameraBuffer() { return cameraConstBuf; };

		// DirectX 11 specific
		ID3D11Device* l_Device;
		ID3D11DeviceContext* l_DeviceContext;

		ID3D11RenderTargetView* currentRTV;
		ID3D11DepthStencilView* currentDSV;
	private:

		bool CreateDefaultRenderTargetView();
		bool CreateDepthStencilView();

		void CreateViewport();

		void InitDefferedRenderingBuffer();
		void DestroyDefferedRenderingBuffer();

		void InitScreenQuad();

		void BindFirstPass();
		void BindLastPass();

		RSRender_Buffer* cameraConstBuf;
		cameraConst cb_Camera;

		// Private DX11
		IDXGISwapChain* l_SwapChain;

		D3D11_VIEWPORT viewport;

		// Default screen render target / depth stencil
		ID3D11RenderTargetView* renderTargetView;
		ID3D11Texture2D* depthStencilBuffer;
		ID3D11DepthStencilView* depthStencilView;

		bool RenderDeffered;
		RSRenderTarget* graphicsBuffer[BUFFER_COUNT];
		RSRenderPipeline* screenQuadPipeline = nullptr;

		bool RenderToEditor = false;
		RSRenderTarget* editorRT;
	};

	////LEGACY LEGACY LEGACY////
	extern Vector2 renderResolution;
	extern bool g_Fullscreen;

	extern RenderClass* g_RSRender;

}

#endif // _RSRENDER_H_
