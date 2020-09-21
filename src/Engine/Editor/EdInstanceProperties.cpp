/*

RSEngine
Copyright (c) 2020 Mason Lee Back

File name: EdInstanceProperties.cpp

*/

#include <Editor/EdInstanceProperties.h>
#include <Editor/EdClassHelper.h>

#include <Renderer/RSRender.h>

namespace rs {
    namespace Editor {
        std::shared_ptr<Instance> currentInstance = nullptr;

        void InstanceProperties::Initialize() {

        }

        void InstanceProperties::Draw(bool* p_open) {
            if (ImGui::Begin("Properties", p_open, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse)) {
                ImGui::SetWindowPos(ImVec2{ g_RSRender->getWindowResolution().X - 300.0f, g_RSRender->getWindowResolution().Y /2 });
                ImGui::SetWindowSize(ImVec2{ 300.0f, g_RSRender->getWindowResolution().Y / 2 });
            }

            if (currentInstance != nullptr) {
                std::string InstanceClass = currentInstance->getClassName();
                for (auto mClass : classVector) {
                    if (mClass->ClassName == InstanceClass) {
                        mClass->drawFunc(currentInstance);
                    }
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
