/*

RSEngine
Copyright (c) 2019 Mason Lee Back

File name: EdInstanceView.cpp

*/

#include <RSEngine.h>

namespace rs {
    namespace Editor {
        void IterateInstances(std::shared_ptr<Instance> ins) {
            std::vector<std::shared_ptr<Instance>> kids = ins->GetChildren();

            if (kids.size() != 0) {
                for (std::vector<std::shared_ptr<Instance>>::size_type i = 0; i != kids.size(); i++) {
                    std::shared_ptr<Instance> kid = kids[i];
                    if (ImGui::TreeNode((kid->Name + " (" + kid->ClassName + ")").c_str())) {
                        IterateInstances(kid);
                        ImGui::TreePop();
                    }
                }
            }
        }
        
        void InstanceView::Draw(bool* p_open) {
            if (ImGui::Begin("Instances", p_open, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse)) {
                ImGui::SetWindowPos(ImVec2{ (float)g_resX - 300.0f, 26.0f });
                ImGui::SetWindowSize(ImVec2{ 300.0f, (float)g_resY - 26.0f });
                IterateInstances(eng);
            }
            ImGui::End();
        }

    } // namespace Editor
} // namespace rs
