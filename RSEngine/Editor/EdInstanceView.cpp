/*

RSEngine
Copyright (c) 2019 Mason Lee Back

File name: EdInstanceView.cpp

*/

#include <Editor/EdInstanceProperties.h>
#include <Editor/EdInstanceView.h>

#include <Renderer/RSRender.h>

namespace rs {
    namespace Editor {
        void IterateInstances(std::shared_ptr<Instance> ins) {
            for (auto kid : ins->GetChildren()) {
                if (ImGui::TreeNode((kid->GetName() + " (" + kid->ClassName + ")").c_str())) {
                    if (ImGui::Button("Edit instance")) {
                        currentInstance = kid;
                    }
                    if (ImGui::TreeNode("Children")) {
                        IterateInstances(kid);
                        ImGui::TreePop();
                    }
                    ImGui::TreePop();
                }
            }
        }
        
        void InstanceView::Draw(bool* p_open) {
            if (ImGui::Begin("Instances", p_open, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse)) {
                ImGui::SetWindowPos(ImVec2{ (float)g_resX - 300.0f, 26.0f });
                ImGui::SetWindowSize(ImVec2{ 300.0f, ((float)g_resY / 2) - 26.0f });
                IterateInstances(currentLevelRoot);
            }
            ImGui::End();
        }

    } // namespace Editor
} // namespace rs
