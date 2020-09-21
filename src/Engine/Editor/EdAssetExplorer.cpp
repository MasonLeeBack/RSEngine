/*

RSEngine
Copyright (c) 2020 Mason Lee Back

File name: EdAssetExplorer.cpp

*/

#include <Editor/EdAssetExplorer.h>
#include <Renderer/RSRender.h>

using namespace rs::Renderer;

namespace rs {
    namespace Editor {
        bool Initialized = false;

        void AssetExplorer::Initialize() {

        }

        void AssetExplorer::Draw(bool * p_open) {
            if (ImGui::Begin("Asset Explorer", p_open, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse)) {
                ImGui::SetWindowPos(ImVec2{ 0.0f, 26.0f });
                ImGui::SetWindowSize(ImVec2{ 300.0f, (float)g_RSRender->getWindowResolution().Y - 26.0f });
            }

            const ImU32 col = ImGui::GetColorU32(ImGuiCol_ButtonHovered);
            ImVec2 vWindowSize = ImGui::GetWindowSize();
            ImGui::SetCursorPos(ImVec2{ vWindowSize.x/2-60, vWindowSize.y/2-60 });

            const char* text = "Please wait while the asset explorer loads...";
            ImVec2 vTextSize = ImGui::CalcTextSize(text);
            ImGui::SetCursorPos(ImVec2{ (vWindowSize.x / 2) - (vTextSize.x / 2), vWindowSize.y / 2 + 80 });
            ImGui::Text(text);

            ImGui::End();
        }
        
    } // namespace Editor
} // namespace rs
