/*

RSEngine
Copyright (c) 2019 Mason Lee Back

File name: EdInstanceProperties.cpp

*/

#include "Include/EdInstanceProperties.h"
#include <Render/ThirdParty/ImGui/imgui.h>
#include <Render/RSRender.h>

namespace rs {
    namespace Editor {

        std::shared_ptr<Instance> currentInstance = nullptr;

        void InstanceProperties::Draw(bool* p_open) {
            if (ImGui::Begin("Properties", p_open, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse)) {
                ImGui::SetWindowPos(ImVec2{ (float)renderResX - 300.0f, (float)renderResY /2 });
                ImGui::SetWindowSize(ImVec2{ 300.0f, (float)renderResY / 2 });
                
                if (currentInstance != nullptr) {
                    
                }


            }
            ImGui::End();
        }

        void InstanceProperties::SelectInstance(std::shared_ptr<Instance> instance)
        {
            currentInstance = instance;
        }

    } // namespace Editor
} // namespace rs
