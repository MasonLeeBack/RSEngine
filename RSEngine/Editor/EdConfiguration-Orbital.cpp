/*

Orbital-ng
placeholder copyright stuff (c) 2019

*/

#include <RSEngine.h>

namespace rs {
    namespace Editor {
        bool EOrbitalConfig::Initialize()
        {
            return true;
        }

        void EOrbitalConfig::Draw(bool* p_open)
        {
            ImGui::SetNextWindowSize(ImVec2{ 500.0f, 500.0f });
            if (ImGui::Begin("Orbital configuration", p_open, ImGuiWindowFlags_NoResize)) {


            }
            ImGui::End();
        }

    } // namespace Editor
} // namespace rs
