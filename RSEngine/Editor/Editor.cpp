/*

RSEngine
Copyright (c) 2019 Mason Lee Back

File name: Editor.cpp

*/

#include <RSEngine.h>
#include <Editor/EditorStyle.h>

namespace rs {
	using namespace Editor;
	CEditor* g_Editor;

	std::vector<ImFont*> fonts;

	EConsole ec;
	AssetExplorer ae;
	InstanceView iv;
	Viewport vp;
    EOrbitalConfig eoc;

	bool CEditor::Initialize() {
		SetEditorStyle();

		ImGuiIO& io = ImGui::GetIO();
		fonts.push_back(io.Fonts->AddFontFromFileTTF("data/fonts/SourceSansPro-Regular.ttf", 16.0f));

        //
        // Reroute rendering output to editor viewport
        //
        g_Renderer->RenderToEditor();
		
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

	bool CEditor::Update() {
		static bool show_new_instance = false;
		static bool show_console = true;
		static bool show_asset_explorer = true;
		static bool show_instance_list = true;
		static bool show_viewport = true;
        static bool show_orbitalconfig = false;

		ImGui::PushFont(fonts.back());

		if (show_new_instance)   showNewInstance(&show_new_instance);
		if (show_console)		 ec.Draw(&show_console);
		if (show_asset_explorer) ae.Draw(&show_asset_explorer);
		if (show_instance_list)  iv.Draw(&show_instance_list);
		if (show_viewport)       vp.Draw(&show_viewport);
        if (show_orbitalconfig)  eoc.Draw(&show_orbitalconfig);

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
            ImGui::MenuItem("Orbital configuration...", "", &show_orbitalconfig, true);
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("View")) {
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

        g_Renderer->RenderToWindow();

		return true;
	}

} // namespace rs
