/*

RSEngine
Copyright (c) 2019 Mason Lee Back

File name: Editor.cpp

*/

#include <Core/Engine.h>
#include <Editor/Editor.h>
#include <Editor/EditorStyle.h>

#include <Editor\EdClassHelper.h>
#include <Editor\EditorComponent.h>
#include <Editor\EdViewport.h>
#include <Editor\EdInstanceView.h>
#include <Editor\EdInstanceProperties.h>
#include <Editor\EdConsole.h>
#include <Editor\EdAssetExplorer.h>
#include <Editor\EdUtilities.h>

namespace rs {
	using namespace Editor;
	CEditor* g_Editor;

	std::vector<ImFont*> fonts;

	EConsole ec;
	AssetExplorer ae;
	InstanceView iv;
    InstanceProperties ip;
	Viewport vp;
    
	bool CEditor::Initialize() {
		SetEditorStyle();

		ImGuiIO& io = ImGui::GetIO();
		io.IniFilename = NULL;
		fonts.push_back(io.Fonts->AddFontFromFileTTF("data/fonts/SourceSansPro-Regular.ttf", 16.0f));

		ec.Initialize();
		vp.Initialize();
		//ae.Initialize(); 

		ClassHelper_Initialize();

		NewInstance(editorCamera, Camera);
		editorCamera->EyePos = Vector3(-3, 0, 0);

        //
        // Reroute rendering output to editor viewport
        //
        //g_Renderer->RenderToEditor();
		
		return true;
	}

	bool showNewInstance(bool* p_open) {
		ImGui::SetNextWindowSize(ImVec2{ 200.0f, 200.0f });
		if (ImGui::Begin("New Instance...", p_open, ImGuiWindowFlags_NoResize)) {

			const char* items[] = { "AAAA", "BBBB", "CCCC", "DDDD", "EEEE", "FFFF", "GGGG", "HHHH", "IIII", "JJJJ", "KKKK", "LLLLLLL", "MMMM", "OOOOOOO", "PPPP", "QQQQQQQQQQ", "RRR", "SSSS" };
			static const char* current_item = NULL;

			if (ImGui::BeginCombo("##combo", current_item)) // The second parameter is the label previewed before opening the combo.
			{
				for (int n = 0; n < IM_ARRAYSIZE(items); n++)
				{
					bool is_selected = (current_item == items[n]); // You can store your selection however you want, outside or inside your objects
					if (ImGui::Selectable(items[n], is_selected))
						current_item = items[n];
						if (is_selected)
							ImGui::SetItemDefaultFocus();   // You may set the initial focus when opening the combo (scrolling + for keyboard navigation support)
				}
				ImGui::EndCombo();
			}

			if (ImGui::Button("OK", ImVec2(89, 0))) {
				p_open = false;
			}
			ImGui::SetItemDefaultFocus();
			ImGui::SameLine();
			if (ImGui::Button("Cancel", ImVec2(89, 0))) { p_open = false; }
		}
		ImGui::End();
		return true;
	}

	bool CEditor::Update() {
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
			if (ImGui::MenuItem("New", "CTRL+N", nullptr, true)) {
				std::shared_ptr<LevelRoot> newLevel = LevelRoot::newInstance(eng);
				newLevel->LevelName = "New Level (" + std::to_string(levels.size()) + ")";
				levels.push_back(newLevel);

				std::shared_ptr<Camera> thisCam = Camera::newInstance(newLevel);
				thisCam->EyePos = Vector3(-3, 0, 0);

				std::shared_ptr<Part> Base = Part::newInstance(newLevel);
				Base->Size = Vector3(256, 1, 256);
				Base->Position = Vector3(0, -1, 0);
				Base->Name = "Baseplate";

				currentLevelRoot = newLevel;
			}
			if (ImGui::MenuItem("Open...", "CTRL+O", nullptr, false)) {

			}
			if (ImGui::MenuItem("Save", "CTRL+S", nullptr, false)) {

			}
			if (ImGui::MenuItem("Save as...", "", nullptr, false)) {

			}
			ImGui::Separator();
			if (ImGui::MenuItem("Exit")) {
				g_RSCallExit = true;
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
		if (ImGui::BeginMenu("Plugins")) {
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
		return true;
	}

	bool CEditor::Shutdown() {

        //g_Renderer->RenderToWindow();

		return true;
	}

} // namespace rs
