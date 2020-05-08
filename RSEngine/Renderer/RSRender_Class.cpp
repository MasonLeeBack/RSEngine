/*

RSEngine
Copyright (c) 2020 Mason Lee Back

File name: RSRender_New.cpp

*/

#include <Renderer/RSRender.h>
#include <Classes/RSClasses.h>
#include <Renderer/RSGeometryGenerator.h>

namespace rs::Renderer {

	////LEGACY LEGACY LEGACY////
	ID3D11Buffer* pdx_PixelConst;

	Light mylight;
	psCB cbPerFrame;
	////LEGACY LEGACY LEGACY////

	Vector2 renderResolution;
	bool g_Fullscreen;

	RenderClass* g_RSRender;

	RenderClass::RenderClass()
	{
	}

	RenderClass::~RenderClass()
	{
	}

	bool RenderClass::Initialize()
	{
		if (!InitD3D11())
			return false;
		CreateViewport();

		// Here we create the camera constant buffer (registered to b0 on shaders)
		RSBufferDesc cameraConstDesc;
		cameraConstDesc.mType = RSBufferType::CONST_BUFFER;
		cameraConstDesc.mElementCount = 1;
		cameraConstDesc.mStride = sizeof(cameraConst);

		cameraConstBuf = new RSRender_Buffer(cameraConstDesc);
		cameraConstBuf->Initialize(&cb_Camera);

		// Assign b0


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
		renderResolution = Vector2(static_cast<float>(g_resX), static_cast<float>(g_resY));

		DXGI_MODE_DESC BufferDesc;
		ZeroMemory(&BufferDesc, sizeof(DXGI_MODE_DESC));

		BufferDesc.Width = renderResolution.X;
		BufferDesc.Height = renderResolution.Y;
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
		SwapChainDesc.OutputWindow = g_hWnd;
		SwapChainDesc.Windowed = !g_Fullscreen;
		SwapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

		result = D3D11CreateDeviceAndSwapChain(
			NULL,
			D3D_DRIVER_TYPE_HARDWARE,
			NULL,
			NULL,
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
			RSThrowError(L"DirectX 11 failed to initialize.");
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
		//l_DeviceContext->OMSetRenderTargets(1, NULL, NULL);

		// Clear render target view
		if (renderTargetView)
			renderTargetView->Release();
		if (depthStencilBuffer)
			depthStencilBuffer->Release();
		if (depthStencilView)
			depthStencilView->Release();

		l_DeviceContext->Flush();

		l_SwapChain->ResizeBuffers(0, resolution.X, resolution.Y, DXGI_FORMAT_UNKNOWN, 0);

		CreateDefaultRenderTargetView();
		CreateDepthStencilView();

		l_DeviceContext->OMSetRenderTargets(1, &prevRTV, prevDSV);

		//DestroyDefferedRenderingBuffer();
		//InitDefferedRenderingBuffer();

		renderResolution = resolution;
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
		currentRTV = rt->getRenderTarget();
		currentDSV = rt->getDepthStencil();
		l_DeviceContext->RSSetViewports(1, viewports);
		l_DeviceContext->OMSetRenderTargets(1, &currentRTV, currentDSV);
	}

	void RenderClass::SetDefaultRenderTarget()
	{
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
		screenQuadPipeline->VertexBuffer->Initialize(&(mesh.vertexMap.front()));

		RSBufferDesc indexDesc;
		indexDesc.mType = RSBufferType::INDEX_BUFFER;
		indexDesc.mElementCount = mesh.vertexIndices.size();
		indexDesc.mStride = sizeof(unsigned int);

		screenQuadPipeline->IndexBuffer = new RSRender_Buffer(vertDesc);
		screenQuadPipeline->IndexBuffer->Initialize(&(mesh.vertexIndices.front()));
	}

	void RenderClass::BindFirstPass()
	{
		ID3D11RenderTargetView* renderTargets[] = {
			graphicsBuffer[0]->renderTargetView,
			graphicsBuffer[1]->renderTargetView,
			graphicsBuffer[2]->renderTargetView
		};
		l_DeviceContext->OMSetRenderTargets(BUFFER_COUNT, renderTargets, depthStencilView);

		float color_defaultview[] = { .3, .5, .3, 1 };
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

		//hBindLastPass();

		if (RenderToEditor)
			SetDefaultRenderTarget();

		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		// If any ImGui subcomponents (i.e. Editor) need to be updated,
		// now is the time to do so.
		g_Editor->Update();

		ImGui::Render();
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

		l_SwapChain->Present(1, 0);
	}

} // namespace rs::Renderer
