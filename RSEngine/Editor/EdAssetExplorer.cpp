/*

RSEngine
Copyright (c) 2019 Mason Lee Back

File name: EdAssetExplorer.cpp

*/

#include <RSEngine.h>

namespace rs {
    namespace Editor {
        void AssetExplorer::Draw(bool * p_open) {
            if (ImGui::Begin("Asset Explorer", p_open, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse)) {
                ImGui::SetWindowPos(ImVec2{ 0.0f, 26.0f });
                ImGui::SetWindowSize(ImVec2{ 300.0f, (float)g_resY - 26.0f });
            }
            ImGui::End();
        }
        
    } // namespace Editor
} // namespace rs
