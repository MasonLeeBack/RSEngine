/*

RSEngine
Copyright (c) 2019 Mason Lee Back

File name: Editor.cpp

*/

#include <vector>

#include <Render/ThirdParty/ImGui/imgui.h>

#include <Core/GameLib.h>
#include "Include/Editor.h"

namespace rs {
    using namespace Editor;
#ifndef _ORBIS
	std::vector<ImFont*> fonts;

	EConsole ec;
	AssetExplorer ae;
	InstanceView iv;
    InstanceProperties ip;
	Viewport vp;
    
	bool GameLib::Initialize() {
		SetEditorStyle();

		ImGuiIO& io = ImGui::GetIO();
		fonts.push_back(io.Fonts->AddFontFromFileTTF("data/fonts/SourceSansPro-Regular.ttf", 16.0f));

        //
        // Reroute rendering output to editor viewport
        //
        //g_Renderer->RenderToEditor();
		
		return true;
	}

	bool showNewInstance(bool* p_open) {
		ImGui::SetNextWindowSize(ImVec2{ 200.0f, 200.0f });
		if (ImGui::Begin("New Instance...", p_open, ImGuiWindowFlags_NoResize)) {

			if (ImGui::Button("OK", ImVec2(100, 0))) { p_open = false; }
			ImGui::SetItemDefaultFocus();
			ImGui::SameLine();
			if (ImGui::Button("Cancel", ImVec2(100, 0))) { p_open = false; }
		}
		ImGui::End();
		return true;
	}

	void GameLib::Update() {
        // this doesn't work :(
		static bool show_new_instance = false;
		static bool show_console = true;
		static bool show_asset_explorer = true;
		static bool show_instance_list = true;
        static bool show_instance_properties = true;
		static bool show_viewport = true;

		ImGui::PushFont(fonts.back());

		if (show_new_instance)   showNewInstance(&show_new_instance);
		if (show_console)		 ec.Draw(&show_console);
		if (show_asset_explorer) ae.Draw(&show_asset_explorer);
		if (show_instance_list)  iv.Draw(&show_instance_list);
        if (show_instance_properties) ip.Draw(&show_instance_properties);
		if (show_viewport)       vp.Draw(&show_viewport);

		ImGui::BeginMainMenuBar();
		if (ImGui::BeginMenu("File")) {
			if (ImGui::MenuItem("New", "CTRL+N", nullptr, false)) {

			}
			if (ImGui::MenuItem("Open...", "CTRL+O", nullptr, false)) {

			}
			if (ImGui::MenuItem("Save", "CTRL+S", nullptr, false)) {

			}
			if (ImGui::MenuItem("Save as...", "", nullptr, false)) {

			}
			ImGui::Separator();
			if (ImGui::MenuItem("Exit")) {

			}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Edit")) {
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("View")) {
            ImGui::MenuItem("Asset Explorer", "", &show_asset_explorer, true);
            ImGui::MenuItem("Console", "", &show_console, true);
            ImGui::MenuItem("Engine Instances", "", &show_instance_list, true);
            ImGui::MenuItem("Instance Properties", "", &show_instance_properties, true);
            ImGui::MenuItem("Level Viewport", "", &show_viewport, true);
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Level")) {
			ImGui::MenuItem("New Instance...", "CTRL+N", &show_new_instance, true);
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Help")) {
			if (ImGui::MenuItem("Help & Support...", "CTRL+?", nullptr, false)) {

			}
			if (ImGui::MenuItem("About RSEngine")) {

			}
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();

		ImGui::PopFont();
	}

	void GameLib::Shutdown() {

        //g_Renderer->RenderToWindow();

	}

#endif

#ifdef _ORBIS
    bool CEditor::Initialize() {
        return true;
    }

    bool CEditor::Update() {
        return true;
    }

    bool CEditor::Shutdown() {
        return true;
    }
#endif

} // namespace rs
