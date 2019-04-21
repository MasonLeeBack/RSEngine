/*

RSEngine
Copyright (c) 2019 Mason Lee Back

File name: EdViewport.cpp

*/

#include <RSEngine.h>

namespace rs {
    namespace Editor {
        void Viewport::Draw(bool* p_open) {
            ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.4f, 0.4f, 0.4f, 1.0f));
            if (ImGui::Begin("Level (TestLevel)", p_open, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse)) {
                ImGui::SetWindowPos(ImVec2{ 300.0f, 26.0f });
                ImGui::SetWindowSize(ImVec2{ (float)g_resX - 600.0f, (float)g_resY - 226.0f });
            }
            ImGui::End();
            ImGui::PopStyleColor();
        }
    
    } // namespace Editor
} // namespace rs
