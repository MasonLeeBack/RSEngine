/*

RSEngine
Copyright (c) 2020 Mason Lee Back

File name: EdInstanceView.cpp

*/

#include <Editor/EdInstanceProperties.h>
#include <Editor/EdInstanceView.h>

#include <Renderer/RSRender.h>

namespace rs {
    namespace Editor {
        void IterateInstances(std::shared_ptr<Instance> ins) {
            /*for (auto kid : ins->GetChildren()) {
                ImGuiTreeNodeFlags node_flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick;
                bool open = ImGui::TreeNode((kid->GetName() + " (" + kid->ClassName + ")").c_str(), node_flags);
                if (ImGui::BeginPopupContextItem())
                {
                    if (ImGui::Button("Delete instance")) {
                        kid->Remove();
                    }
                    ImGui::EndPopup();
                }
                if (open) {
                    if (ImGui::Button("Edit instance")) {
                        currentInstance = kid;
                    }

                    if (ImGui::TreeNode("Children")) {
                        IterateInstances(kid);
                        ImGui::TreePop();
                    }
                    ImGui::TreePop();
                }
            }*/

            ImGui::LabelText("Game objects in scene:", "");

            if (ImGui::TreeNode("Object List"))
            {
                ImGui::PushStyleVar(ImGuiStyleVar_IndentSpacing, ImGui::GetFontSize() * 3);
                for (int i = 0; i < ins->children.size(); i++)
                {
                    ImGuiTreeNodeFlags node_flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick;
                    bool node_open = ImGui::TreeNodeEx((void*)(intptr_t)i, node_flags, ins->children[i]->Name.c_str());

                    //treeChildren(node_flags, node_open, i);

                    if (node_open)
                    {
                        ImGui::TreeNodeEx((void*)(intptr_t)i, node_flags, "child two");
                        ImGui::TreePop();
                    }
                }
                ImGui::TreePop();
                ImGui::PopStyleVar();
                
            }
        }
        
        void InstanceView::Draw(bool* p_open) {
            if (ImGui::Begin("Instances", p_open, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse)) {
                ImGui::SetWindowPos(ImVec2{ g_RSRender->getWindowResolution().X - 300.0f, 26.0f });
                ImGui::SetWindowSize(ImVec2{ 300.0f, (g_RSRender->getWindowResolution().Y / 2) - 26.0f });
                IterateInstances(currentLevelRoot);
            }
            ImGui::End();
        }

    } // namespace Editor
} // namespace rs
