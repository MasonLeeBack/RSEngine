/*

RSEngine
Copyright (c) 2020 Mason Lee Back

File name: Engine.cpp

*/

#include <future>
#include <iostream>

#include <Classes/RSClasses.h>

#include <Core/Engine.h>
#include <Editor/Editor.h>
#include <Input/RareInput.h>
#include <Renderer/RSRender.h>
using namespace rs::Renderer;
#include <UI/RSEngine_UI.h>
using namespace rs::UI;
#include <Core/Console.h>
#include <Core/GameLib.h>
#include <Physics/RSPhysics.h>
#include <Window/WindowSystem.h>
#include <Parser/RareParser.h>
#include <Core/Timer.h>
using namespace rs::Physics;

namespace rs {
    RSEngine* g_Engine;
    bool g_GameActive = true;

    extern std::shared_ptr<LevelRoot> currentLevelRoot;

    std::shared_ptr<Engine> eng;

    RSEngine::RSEngine()
    {
        // Engine initiailizes all components here :)

        // Engine instance for base game
        eng = std::make_shared<Engine>();

        //Parse the XML file (if it exists)
        m_pParser = new RareParser;
        m_pParser->SetEngineAttributes();
        
        WindowClassConfig cfg = m_pParser->getWindowConfiguration();

        m_pWindowManager = new Window(cfg);

        g_Input = new CInput;
        if (!g_Input->Init()) {
            return;
        }

        g_RSRender = new RenderClass(this);
        if (!g_RSRender->Initialize()) {
            return;
        }

        g_RSPhysics = new PhysicsSystem;
        if (!g_RSPhysics->Initialize()) {
            return;
        }

        m_pRareUI = new RareUI(m_pWindowManager);
        m_pEditor = new CEditor(this);
        if (!m_pEditor->Initialize()) {
#ifdef _EDITOR
            return;
#endif // _EDITOR
            // We can live without the editor.
            std::cout << "Editor failed to initialize." << std::endl;
        }

        g_Console = new Console;
        if (!g_Console->Initialize()) {
#ifdef _EDITOR
            return;
#endif // _EDITOR
            // We can live without the console.
            std::cout << "Console failed to initialize." << std::endl;
        }

        // Initialize timer class
        m_pTimer = new Timer();
        m_pTimer->reset();
    }

    RSEngine::~RSEngine()
    {
        g_Input->Shutdown();
        g_RSRender->Shutdown();
        g_RSPhysics->Shutdown();
        delete m_pEditor;
        m_pEditor = nullptr;
        delete m_pRareUI;
        m_pRareUI = nullptr;
        g_Console->Shutdown();
        g_GameLib->Shutdown();
        m_pTimer->stop();

        delete g_Input;
        g_Input = nullptr;
        delete g_RSRender;
        g_RSRender = nullptr;
        delete g_RSPhysics;
        g_RSPhysics = nullptr;
        delete g_Console;
        g_Console = nullptr;
        delete g_GameLib;
        g_GameLib = nullptr;
        delete m_pTimer;
        m_pTimer = nullptr;
    }

    bool RSEngine::Init() {
        std::shared_ptr<LevelRoot> defaultLevel = LevelRoot::newInstance(eng);
        defaultLevel->LevelName = "New Level";
        currentLevelRoot = defaultLevel;
        NewInstance(gCamera, Camera);
        gCamera->EyePos = Vector3(0, 0, -3);
        levels.push_back(defaultLevel);

        g_GameLib = new GameLib;
        g_GameLib->Initialize();

        

        GameLoop();

        // Shut down after the game loop ends.
        Shutdown();

        return true;
    }

    Window* RSEngine::getWindowManager()
    {
        return m_pWindowManager;
    }

    CEditor* RSEngine::getEditor()
    {
        return m_pEditor;
    }

    int RSEngine::GameLoop() {
        MSG msg;
        ZeroMemory(&msg, sizeof(MSG));

        while (true) {
            if (m_RSCallExit == true) {
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
                m_pTimer->tick();
                g_GameLib->Update();
                g_RSPhysics->Update();
                eng->tick();
                g_Input->Update();
                g_RSRender->DrawScene();
            }
        }

        return (int)msg.wParam;
        return 0;
    }

    void RSEngine::Shutdown() {
        g_GameLib->Shutdown();
        delete g_GameLib;
    }

    void RSEngine::CallForExit(int status)
    {
        m_ExitStatus = status;
        m_RSCallExit = true;
    }

    std::shared_ptr<rs::Engine> getEngineInstance() {
        return eng;
    }

} // namespace rs
