/*

RSEngine
Copyright (c) 2019 Mason Lee Back

File name: EdInstanceView.cpp

*/

#include "Include/EdInstanceView.h"
#include <Render/ThirdParty/ImGui/imgui.h>
#include <Render/RSRender.h>
#include <Core/Engine.h>

namespace rs {
    namespace Editor {
        void IterateInstances(std::shared_ptr<Instance> ins) {
            for (auto kid : ins->GetChildren()) {
                if (ImGui::TreeNode((kid->GetName() + " (" + kid->ClassName + ")").c_str())) {
                    IterateInstances(kid);
                    ImGui::TreePop();
                }
            }
        }
        
        void InstanceView::Draw(bool* p_open) {
            if (ImGui::Begin("Instances", p_open, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse)) {
                ImGui::SetWindowPos(ImVec2{ (float)renderResX - 300.0f, 26.0f });
                ImGui::SetWindowSize(ImVec2{ 300.0f, ((float)renderResY / 2) - 26.0f });
                IterateInstances(eng);
            }
            ImGui::End();
        }

    } // namespace Editor
} // namespace rs
