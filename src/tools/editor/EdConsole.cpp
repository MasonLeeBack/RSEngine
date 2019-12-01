/*

RSEngine
Copyright (c) 2019 Mason Lee Back

File name: EdConsole.cpp

*/

#include "Include/EdConsole.h"
#include <Render/ThirdParty/ImGui/imgui.h>
#include <Render/RSRender.h>
#include <Core/Engine.h>

namespace rs {
    namespace Editor {
        void EConsole::Draw(bool* p_open)  {
            if (ImGui::Begin("Console", p_open, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse)) {
                ImGui::SetWindowPos(ImVec2{ 300.0f, (float)renderResY - 200.0f });
                ImGui::SetWindowSize(ImVec2{ (float)renderResX - 600.0f, 200.0f });
            }
            ImGui::End();
        }

    } // namespace Editor
} // namespace rs
