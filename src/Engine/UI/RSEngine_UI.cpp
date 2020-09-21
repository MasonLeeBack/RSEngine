/*

RSEngine
Copyright (c) 2020 Mason Lee Back

File name: RSEngine_UI.cpp

Abstract: ImGui-specific initialization and shutdown
		  routines

*/

#include <Renderer/RSRender.h>
using namespace rs::Renderer;

#include <ThirdParty/ImGui/imgui.h>
#include <ThirdParty/ImGui/imgui_impl_dx11.h>
#include <ThirdParty/ImGui/imgui_impl_win32.h>

#include <Window/WindowSystem.h>

#include <UI/RSEngine_UI.h>

namespace rs::UI {

	RareUI* g_rareUI;

	RareUI::RareUI(Window* windowSystem)
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		auto& io = ImGui::GetIO();
		io.IniFilename = NULL;

		if (!ImGui_ImplWin32_Init(windowSystem->getWindowHandle())) return;
		if (!ImGui_ImplDX11_Init(g_RSRender->l_Device, g_RSRender->l_DeviceContext)) return;
	}

	RareUI::~RareUI()
	{
#ifdef _WIN32
		ImGui_ImplDX11_Shutdown();
		ImGui_ImplWin32_Shutdown();
#endif
		ImGui::DestroyContext();
	}

} // namespace rs::UI
