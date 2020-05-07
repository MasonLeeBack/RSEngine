/*

RSEngine
Copyright (c) 2019 Mason Lee Back

File name: EdViewport.cpp

*/

#include <Editor/EdViewport.h>
#include <Renderer/RSRender.h>
using namespace rs::Renderer;

namespace rs {
    namespace Editor {
        RSRenderTarget* editorRT;

        bool Viewport::Initialize() {
            editorRT = new RSRenderTarget(Vector2(800, 800));

            g_RSRender->EnableEditorRenderTarget(true, editorRT);

            return true;
        }

        void Viewport::Draw(bool* p_open) {
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
            ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.4f, 0.4f, 0.4f, 1.0f));
            if (ImGui::Begin("Level (TestLevel)", p_open, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse)) {
                ImGui::SetWindowPos(ImVec2{ 300.0f, 26.0f });
                ImGui::SetWindowSize(ImVec2{ (float)g_resX - 600.0f, (float)g_resY - 226.0f });

                //
                // Set the viewport resolution to the window size
                //
                ImVec2 WindowSize = ImGui::GetWindowSize();
                WindowSize.y = WindowSize.y - 26.0f;

                editorRT->Resize(Vector2(WindowSize.x, WindowSize.y));
                ImGui::Image(editorRT->getSRV(), WindowSize, ImVec2(0, 0), ImVec2(1, 1));

                //g_Renderer->UpdateViewportSize(WindowSize.x, WindowSize.y);
                //ImGui::Image(g_Renderer->GetRenderedTexture(), WindowSize, ImVec2(0, 0), ImVec2(1, 1));

            }
            ImGui::End();
            ImGui::PopStyleColor();
            ImGui::PopStyleVar();
        }
    
    } // namespace Editor
} // namespace rs
