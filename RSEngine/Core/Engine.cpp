/*

RSEngine
Copyright (c) 2019 Mason Lee Back

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

File name: Engine.cpp

*/

#include <future>
#include <iostream>

#include <Core/Engine.h>
#include <Core/Filesystem.h>
#include <Input/RareInput.h>
#include <Renderer/RSRender.h>
using namespace rs::Renderer;
#include <UI/RSEngine_UI.h>
using namespace rs::UI;
#include <Core/Console.h>
#include <Core/GameLib.h>

namespace rs {
    RSEngine* g_Engine;
    bool g_GameActive = true;
    bool g_RSCallExit = false;

    extern std::shared_ptr<LevelRoot> currentLevelRoot;

    std::shared_ptr<Engine> eng;

    bool RSEngine::Init() {
        // Engine instance is initialized here.
        eng = std::make_shared<Engine>();

        g_Filesystem = new Filesystem;
        if (!g_Filesystem->Init()) {
            return false;
        }

        g_Input = new CInput;
        if (!g_Input->Init()) {
            return false;
        }

        g_RSRender = new RenderClass;
        if (!g_RSRender->Initialize()) {
            return false;
        }

        g_rareUI = new RareUI;
        if (g_rareUI->Initialize()) {
            g_Editor = new CEditor;
            if (!g_Editor->Initialize()) {
#ifdef _EDITOR
                return false;
#endif // _EDITOR
                // We can live without the editor.
                std::cout << "Editor failed to initialize." << std::endl;
            }
        }

        g_Console = new Console;
        if (!g_Console->Initialize()) {
#ifdef _EDITOR
            return false;
#endif // _EDITOR
            // We can live without the console.
            std::cout << "Console failed to initialize." << std::endl;
        }

        //g_GameLib = new GameLib;
        //std::future<void> ff = std::async(std::launch::async, g_GameLib->Initialize);

        std::shared_ptr<LevelRoot> defaultLevel = LevelRoot::newInstance(eng);
        defaultLevel->LevelName = "New Level";
        currentLevelRoot = defaultLevel;
        NewInstance(gCamera, Camera);
        gCamera->EyePos = Vector3(-3, 0, 0);
        levels.push_back(defaultLevel);

        GameLoop();

        // Shut down after the game loop ends.
        Shutdown();

        return true;
    }

    int RSEngine::GameLoop() {
        MSG msg;
        ZeroMemory(&msg, sizeof(MSG));

        while (true) {
            if (g_RSCallExit == true) {
                // Do more shutdown stuff at a later time.
                break;
            }
            if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
                if (msg.message == WM_QUIT) {
                    break;
                }
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
            else {
                g_GameLib->Update();
                eng->tick();
                g_Input->Update();
                g_RSRender->DrawScene();
            }
        }

        return (int)msg.wParam;
        return 0;
    }

    void RSEngine::Shutdown() {
        g_Input->Shutdown();
        g_Filesystem->Shutdown();
        g_RSRender->Shutdown();
        g_Editor->Shutdown();
        g_rareUI->Shutdown();
        g_Console->Shutdown();
        g_GameLib->Shutdown();

        delete g_Input;
        g_Input = nullptr;
        delete g_Filesystem;
        g_Filesystem = nullptr;
        delete g_RSRender;
        g_RSRender = nullptr;
        delete g_Editor;
        g_Editor = nullptr;
        delete g_Console;
        g_Console = nullptr;
        delete g_GameLib;
        g_GameLib = nullptr;
    }

    std::shared_ptr<rs::Engine> getEngineInstance() {
        return eng;
    }

} // namespace rs
