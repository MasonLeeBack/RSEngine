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

File name: Engine.h

*/

#pragma once
#ifndef _Game_h_
#define _Game_h_

#define _EDITOR 1

namespace rs {
    class Window;
    class RareParser;
    class Timer;
    class CEditor;
    class LevelManager;

    namespace UI {
        class RareUI;
    }

    class RSEngine {
    public:
        RSEngine();
        ~RSEngine();

        bool Init();
        void Shutdown();

        void CallForExit(int status);

        Timer* m_pTimer;

        // get Handlers
        Window* getWindowManager();
#ifdef _EDITOR
        CEditor* getEditor();
#endif
        LevelManager* getLevelManager();

    private:
        int GameLoop();

        Window* m_pWindowManager;
        RareParser* m_pParser;

        LevelManager* m_pLevelManager;
        
#ifdef _EDITOR
        UI::RareUI* m_pRareUI;
        CEditor* m_pEditor;
#endif

        bool m_RSCallExit = false;
        int m_ExitStatus = 0;
    };

    extern RSEngine* g_Engine;

} // namespace rs

#endif // _Game_h_
