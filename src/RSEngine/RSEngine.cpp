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

File name: PolyEngine.cpp

*/

#include <Windows.h>
#include <Window/WindowSystem.h>

#include <Core/Error.h>
#include <Core/Engine.h>
#include <Core/Config.h>

using namespace rs;

#ifdef _WIN32
extern "C" _declspec(dllexport) INT LauncherMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, INT iCmdShow) {
    g_hInstance = hInstance;
    g_iCmdShow = iCmdShow;
    g_CommandLine = lpCmdLine;

    // Initialization
    INT xRes = GetPrivateProfileIntA("RSEngine", "ScreenResolution_X", 1920, "Engine.ini");
    INT yRes = GetPrivateProfileIntA("RSEngine", "ScreenResolution_Y", 1080, "Engine.ini");
    
    Window windowManager;
    if (!windowManager.Init(xRes, yRes)) {
        RSThrowError(L"The window manager failed to create the window.\n");
    }
    
    // Set up global engine class and initialize.
    g_Engine = new RSEngine;
    if (!g_Engine->Init()) {
        RSThrowError(L"RSEngine failed to initialize.\n");
    }
    
    return 0;
}
#endif

#ifdef _ORBIS
int main(int argc, char* argv[])
{
    // Set up global engine class and initialize.
    g_Engine = new RSEngine;
    if (!g_Engine->Init()) {
        RSThrowError(L"RSEngine failed to initialize.");
    }
}
#endif
