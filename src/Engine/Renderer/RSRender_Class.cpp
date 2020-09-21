/*

RSEngine
Copyright (c) 2020 Mason Lee Back

File name: RSRender_Class.cpp

*/

#include <Renderer/RSRender.h>
#include <Classes/RSClasses.h>
#include <Renderer/RSGeometryGenerator.h>

#include <Core/RSErrorHandling.h>
#include <Core/Engine.h>
#include <Window/WindowSystem.h>

#include <Editor/Editor.h>

#include <ThirdParty/ImGui/imgui.h>
#include <ThirdParty/ImGui/imgui_impl_win32.h>
#include <ThirdParty/ImGui/imgui_impl_dx11.h>

#include <comdef.h>

namespace rs::Renderer {

	////LEGACY LEGACY LEGACY////
	ID3D11Buffer* pdx_PixelConst;

	Light mylight;
	psCB cbPerFrame;
	////LEGACY LEGACY LEGACY////

	Vector2 renderResolution;
	bool g_Fullscreen;

	RenderClass* g_RSRender;

	RenderClass::RenderClass(RSEngine* engine)
	{
		l_pEngine = engine;
	}

	RenderClass::~RenderClass()
	{
	}

	bool RenderClass::Initialize()
	{
		if (!InitD3D11())
			return false;
		CreateViewport();

		l_DeviceContext->RSSetViewports(1, &viewport);

		// Here we create the camera constant buffer (registered to b0 on shaders)
		RSBufferDesc cameraConstDesc;
		cameraConstDesc.mType = RSBufferType::CONST_BUFFER;
		cameraConstDesc.mElementCount = 1;
		cameraConstDesc.mStride = sizeof(cameraConst);

		cameraConstBuf = new RSRender_Buffer(cameraConstDesc);
		cameraConstBuf->Initialize(&cb_Camera);

		// Assign b0

		// Set up two rasterizer states - One for culling nothing, and one for culling everything (default)
		D3D11_RASTERIZER_DESC cullAllRasterizerDesc;
		ZeroMemory(&cullAllRasterizerDesc, sizeof(D3D11_RASTERIZER_DESC));
		cullAllRasterizerDesc.CullMode = D3D11_CULL_BACK;
		l_Device->CreateRasterizerState(&cullAllRasterizerDesc, &cullAllRasterizerState);

		D3D11_RASTERIZER_DESC cullNoneRasterizerDesc;
		ZeroMemory(&cullNoneRasterizerDesc, sizeof(D3D11_RASTERIZER_DESC));
		cullNoneRasterizerDesc.FillMode = D3D11_FILL_SOLID;
		cullNoneRasterizerDesc.CullMode = D3D11_CULL_NONE;
		l_Device->CreateRasterizerState(&cullNoneRasterizerDesc, &cullNoneRasterizerState);

		D3D11_BLEND_DESC blendDesc;
		ZeroMemory(&blendDesc, sizeof(blendDesc));

		D3D11_RENDER_TARGET_BLEND_DESC rtbd;
		ZeroMemory(&rtbd, sizeof(rtbd));
		//
		rtbd.BlendEnable = true;
		//rtbd.SrcBlend = D3D11_BLEND_SRC_COLOR;
		//rtbd.DestBlend = D3D11_BLEND_BLEND_FACTOR;
		//rtbd.BlendOp = D3D11_BLEND_OP_ADD;
		//rtbd.SrcBlendAlpha = D3D11_BLEND_ONE;
		//rtbd.DestBlendAlpha = D3D11_BLEND_ZERO;
		//rtbd.BlendOpAlpha = D3D11_BLEND_OP_ADD;
		rtbd.SrcBlend = D3D11_BLEND_SRC_ALPHA;
		rtbd.DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		rtbd.BlendOp = D3D11_BLEND_OP_ADD;
		rtbd.SrcBlendAlpha = D3D11_BLEND_INV_DEST_ALPHA;
		rtbd.DestBlendAlpha = D3D11_BLEND_ONE;
		rtbd.BlendOpAlpha = D3D11_BLEND_OP_ADD;
		rtbd.RenderTargetWriteMask = D3D10_COLOR_WRITE_ENABLE_ALL;

		blendDesc.AlphaToCoverageEnable = false;
		blendDesc.RenderTarget[0] = rtbd;

		l_Device->CreateBlendState(&blendDesc, &transparencyBlendState);

		// Other constant buffers, needs moved
		//// LEGACY LEGACY LEGACY////
		HRESULT hr;

		D3D11_BUFFER_DESC cbbd;
		ZeroMemory(&cbbd, sizeof(D3D11_BUFFER_DESC));

		cbbd.Usage = D3D11_USAGE_DEFAULT;
		cbbd.ByteWidth = sizeof(cbPerFrame);
		cbbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		cbbd.CPUAccessFlags = 0;
		cbbd.MiscFlags = 0;

		hr = l_Device->CreateBuffer(&cbbd, NULL, &pdx_PixelConst);
		//// LEGACY LEGACY LEGACY ////

		InitScreenQuad();

		return true;
	}

	bool RenderClass::InitD3D11()
	{
		HRESULT result;

		// Initial render resolution. This can be changed if we're using
		// a custom viewport or if UpdateSwapChainResolution is called.
		WindowClassConfig cfg = l_pEngine->getWindowManager()->getWindowConfig();
		renderResolution = Vector2(static_cast<float>(cfg.windowWidth), static_cast<float>(cfg.windowHeight));

		DXGI_MODE_DESC BufferDesc;
		ZeroMemory(&BufferDesc, sizeof(DXGI_MODE_DESC));

		BufferDesc.Width = static_cast<unsigned int>(renderResolution.X);
		BufferDesc.Height = static_cast<unsigned int>(renderResolution.Y);
		BufferDesc.RefreshRate.Numerator = 60;
		BufferDesc.RefreshRate.Denominator = 1;
		BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

		DXGI_SWAP_CHAIN_DESC SwapChainDesc;
		ZeroMemory(&SwapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC));

		SwapChainDesc.BufferDesc = BufferDesc;
		SwapChainDesc.SampleDesc.Count = 1;
		SwapChainDesc.SampleDesc.Quality = 0;
		SwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT | DXGI_USAGE_SHADER_INPUT;
		SwapChainDesc.BufferCount = 3;
		SwapChainDesc.OutputWindow = (HWND)l_pEngine->getWindowManager()->getWindowHandle();
		SwapChainDesc.Windowed = !g_Fullscreen;
		SwapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;

		result = D3D11CreateDeviceAndSwapChain(
			NULL,
			D3D_DRIVER_TYPE_HARDWARE,
			NULL,
			D3D11_CREATE_DEVICE_DEBUG,
			NULL,
			NULL,
			D3D11_SDK_VERSION,
			&SwapChainDesc,
			&l_SwapChain,
			&l_Device,
			NULL,
			&l_DeviceContext
		);
		if (FAILED(result)) {
			RSHandleError("DirectX 11 failed to initialize.");
			return false;
		}

		// Create the default render target view.
		if (!CreateDefaultRenderTargetView()) return false;

		// Create our depth stencil view.
		if (!CreateDepthStencilView()) return false;

		InitDefferedRenderingBuffer();

		return true;
	}

	bool RenderClass::CreateDefaultRenderTargetView()
	{
		HRESULT hr;

		ID3D11Texture2D* BackBuffer;
		l_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&BackBuffer);

		hr = l_Device->CreateRenderTargetView(BackBuffer, NULL, &renderTargetView);

		BackBuffer->Release();

		if (FAILED(hr)) return false;

		return true;
	}

	bool RenderClass::CreateDepthStencilView()
	{
		HRESULT hr;
		
		D3D11_TEXTURE2D_DESC depthStencilDesc;

		depthStencilDesc.Width = static_cast<UINT>(renderResolution.X);
		depthStencilDesc.Height = static_cast<UINT>(renderResolution.Y);
		depthStencilDesc.MipLevels = 1;
		depthStencilDesc.ArraySize = 1;
		depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		depthStencilDesc.SampleDesc.Count = 1;
		depthStencilDesc.SampleDesc.Quality = 0;
		depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
		depthStencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		depthStencilDesc.CPUAccessFlags = 0;
		depthStencilDesc.MiscFlags = 0;

		hr = l_Device->CreateTexture2D(&depthStencilDesc, NULL, &depthStencilBuffer);
		if (FAILED(hr)) return false;

		hr = l_Device->CreateDepthStencilView(depthStencilBuffer, NULL, &depthStencilView);
		if (FAILED(hr)) return false;

		return true;
	}

	// Called whenever the screen resolution updates
	void RenderClass::UpdateSwapChainResolution(Vector2 resolution)
	{
		ID3D11RenderTargetView* prevRTV;
		ID3D11DepthStencilView* prevDSV;
		l_DeviceContext->OMGetRenderTargets(1, &prevRTV, &prevDSV);

		// Clear render target view
		if (renderTargetView)
			renderTargetView->Release();
		if (depthStencilView)
			depthStencilView->Release();
		if (depthStencilBuffer)
			depthStencilBuffer->Release();

		l_DeviceContext->Flush();

		HRESULT hr = l_SwapChain->ResizeBuffers(0, static_cast<UINT>(resolution.X), static_cast<UINT>(resolution.Y), DXGI_FORMAT_UNKNOWN, 0);
		if (FAILED(hr)) {
			_com_error err(hr);
			LPCTSTR errMsg = err.ErrorMessage();
			MessageBox(NULL, errMsg, L"CreatePixelShader error", MB_OK);
			return;
		}

		renderResolution = resolution;

		CreateDefaultRenderTargetView();
		CreateDepthStencilView();

		l_DeviceContext->OMSetRenderTargets(1, &prevRTV, prevDSV);

		DestroyDefferedRenderingBuffer();
		InitDefferedRenderingBuffer();

	}

	void RenderClass::AssignShader(RSRender_Shader* shader)
	{
		if (shader == nullptr || !shader->isInitialized())
			return;
		switch (shader->getShaderType()) {
		case RSShaderType::RS_VERTEX_SHADER:
			l_DeviceContext->IASetInputLayout(shader->inputLayout);
			l_DeviceContext->VSSetShader(shader->vertexShader, 0, 0);
			break;
		case RSShaderType::RS_PIXEL_SHADER:
			l_DeviceContext->PSSetShader(shader->pixelShader, 0, 0);
			break;
		}
	}

	void RenderClass::EnableEditorRenderTarget(bool enable, RSRenderTarget* rt)
	{
		RenderToEditor = enable;

		if (enable)
			editorRT = rt;
		else
			editorRT = nullptr;
		
	}

	void RenderClass::SetMultipleRenderTargets(RSRenderTarget* rt, int NumberTargets)
	{

	}

	void RenderClass::SetRenderTarget(RSRenderTarget* rt)
	{
		D3D11_VIEWPORT viewports[] = { rt->getViewport() };
		viewportSize.X = viewports[0].Width;
		viewportSize.Y = viewports[0].Height;
		currentRTV = rt->getRenderTarget();
		currentDSV = rt->getDepthStencil();
		l_DeviceContext->RSSetViewports(1, viewports);
		l_DeviceContext->OMSetRenderTargets(1, &currentRTV, currentDSV);
	}

	void RenderClass::SetDefaultRenderTarget()
	{
		viewportSize.X = viewport.Width;
		viewportSize.Y = viewport.Height;
		currentRTV = renderTargetView;
		currentDSV = depthStencilView;
		l_DeviceContext->RSSetViewports(1, &viewport);
		l_DeviceContext->OMSetRenderTargets(1, &currentRTV, currentDSV);
	}

	void RenderClass::ClearRenderTargetDefault()
	{
		float clearColor[4] = { 0.f, 0.f, 0.f, 1.f };
		float depth = 1.0f;
		uint8_t stencil = 0;

		if (currentRTV) l_DeviceContext->ClearRenderTargetView(currentRTV, clearColor);
		if (currentDSV) l_DeviceContext->ClearDepthStencilView(currentDSV, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, depth, stencil);
	}

	void RenderClass::ClearRenderTarget(float clearColor[4], float depth, uint8_t stencil)
	{
		if (currentRTV) l_DeviceContext->ClearRenderTargetView(currentRTV, clearColor);
		if (currentDSV) l_DeviceContext->ClearDepthStencilView(currentDSV, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, depth, stencil);
	}

	Vector2 RenderClass::GetViewportSize()
	{
		return viewportSize;
	}

	Vector2 RenderClass::getWindowResolution()
	{
		WindowClassConfig config = l_pEngine->getWindowManager()->getWindowConfig();
		return Vector2(static_cast<float>(config.windowWidth), static_cast<float>(config.windowHeight));
	}

	void RenderClass::CreateViewport()
	{
		viewport.TopLeftX = 0;
		viewport.TopLeftY = 0;
		viewport.Width = renderResolution.X;
		viewport.Height = renderResolution.Y;
		viewport.MinDepth = 0.0f;
		viewport.MaxDepth = 1.0f;

		l_DeviceContext->RSSetViewports(1, &viewport);
	}

	void RenderClass::InitDefferedRenderingBuffer()
	{
		for (int i = 0; i < BUFFER_COUNT; i++)
		{
			graphicsBuffer[i] = new RSRenderTarget(renderResolution);
		}
	}

	void RenderClass::DestroyDefferedRenderingBuffer()
	{
		for (UINT i = 0; i < BUFFER_COUNT; i++)
		{
			delete graphicsBuffer[i];
		}
	}

	void RenderClass::InitScreenQuad()
	{
		if (screenQuadPipeline != nullptr)
			return; // screen quad already initialized

		screenQuadPipeline = new RSRenderPipeline;

		GeometryGenerator gen;
		MeshData mesh = gen.GenerateFullscreenQuad();

		RSBufferDesc vertDesc;
		vertDesc.mType = RSBufferType::VERTEX_BUFFER;
		vertDesc.mElementCount = mesh.vertexMap.size();
		vertDesc.mStride = sizeof(vertex);

		screenQuadPipeline->VertexBuffer = new RSRender_Buffer(vertDesc);
		screenQuadPipeline->VertexBuffer->Initialize(mesh.vertexIndices.ptr());

		RSBufferDesc indexDesc;
		indexDesc.mType = RSBufferType::INDEX_BUFFER;
		indexDesc.mElementCount = mesh.vertexIndices.size();
		indexDesc.mStride = sizeof(unsigned int);

		screenQuadPipeline->IndexBuffer = new RSRender_Buffer(vertDesc);
		screenQuadPipeline->IndexBuffer->Initialize(mesh.vertexIndices.ptr());
	}

	void RenderClass::SetCullState(RSCullState cs)
	{
		switch (cs) {
		case RSCullState::CullAll:
			l_DeviceContext->RSSetState(cullAllRasterizerState);
			break;
		case RSCullState::CullNone:
			l_DeviceContext->RSSetState(cullNoneRasterizerState);
			break;
		default:
			break;
		}
	}

	void RenderClass::SetTransparency(float alpha)
	{
		if (alpha > 0.0f) {
			float blendFactor[] = { alpha, alpha, alpha, 0.5f };
			l_DeviceContext->OMSetBlendState(transparencyBlendState, blendFactor, 0xffffffff);
		}
		else {
			l_DeviceContext->OMSetBlendState(0, 0, 0xffffffff);
		}
	}

	void RenderClass::AddToAlphaPass(RSRenderPipeline* pipeline)
	{
		alphaPasses.push(pipeline);
	}

	void RenderClass::BindFirstPass()
	{
		ID3D11RenderTargetView* renderTargets[] = {
			graphicsBuffer[0]->renderTargetView,
			graphicsBuffer[1]->renderTargetView,
			graphicsBuffer[2]->renderTargetView
		};
		l_DeviceContext->OMSetRenderTargets(BUFFER_COUNT, renderTargets, depthStencilView);

		float color_defaultview[] = { .3f, .5f, .3f, 1 };
		l_DeviceContext->ClearRenderTargetView(graphicsBuffer[0]->renderTargetView, color_defaultview);
		float color_deferredpass[] = { 0, 0, 0, 1 };
		l_DeviceContext->ClearRenderTargetView(graphicsBuffer[1]->renderTargetView, color_deferredpass);
		l_DeviceContext->ClearRenderTargetView(graphicsBuffer[2]->renderTargetView, color_deferredpass);
		l_DeviceContext->ClearDepthStencilView(depthStencilView, D3D11_CLEAR_DEPTH, 1, 0);

		l_DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	}

	void RenderClass::BindLastPass()
	{
		l_DeviceContext->OMSetRenderTargets(1, &renderTargetView, nullptr);
		float color_white[] = { 1,1,1,1 };
		l_DeviceContext->ClearRenderTargetView(renderTargetView, color_white);
		l_DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	}

	void RenderClass::renderAlphaPass()
	{
		for (int i = 0; i == alphaPasses.size(); i++) {
			alphaPasses.ptr()[i]->Draw(true);
		}
	}

	void RenderClass::Shutdown()
	{
		if (l_SwapChain != nullptr) l_SwapChain->Release();
		if (l_Device != nullptr) l_Device->Release();
		if (l_DeviceContext != nullptr) l_DeviceContext->Release();
		if (renderTargetView != nullptr) renderTargetView->Release();
		if (depthStencilView != nullptr) depthStencilView->Release();
		if (depthStencilBuffer != nullptr) depthStencilBuffer->Release();
	}

	void RenderClass::DrawScene()
	{
		alphaPasses.clear();

		// Why are we doing this here ///////////
		mylight.dir = DirectX::XMFLOAT3(0.25f, 0.5f, -1.0f);
		mylight.ambient = DirectX::XMFLOAT4(0.2f, 0.2f, 0.2f, 1.0f);
		mylight.diffuse = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);

		cbPerFrame.light = mylight;
		l_DeviceContext->UpdateSubresource(pdx_PixelConst, 0, NULL, &cbPerFrame, 0, 0);
		l_DeviceContext->PSSetConstantBuffers(0, 1, &pdx_PixelConst);
		// Why are we doing this here ///////////

		/* First render pass - Done on screen / or editor */
		SetDefaultRenderTarget();
		ClearRenderTargetDefault();

		if (RenderToEditor) {
			SetRenderTarget(editorRT);
			ClearRenderTargetDefault();
		}

		//BindFirstPass();

		eng->render();

		// We take care of this after calling eng->Render, since
		// any objects with alpha will be sent to the alphaPasses vector.
		renderAlphaPass();

		//BindLastPass();

		//TODO: Combine deferred rendering passes.

		if (RenderToEditor)
			SetDefaultRenderTarget();
		
		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		// If any ImGui subcomponents (i.e. Editor) need to be updated,
		// now is the time to do so.
		l_pEngine->getEditor()->Update();

		ImGui::Render();
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
		
		l_SwapChain->Present(1, 0);
	}

} // namespace rs::Renderer
