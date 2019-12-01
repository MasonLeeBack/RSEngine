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

File name: WindowSystem.cpp

*/

#define _WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <Window/WindowSystem.h>

#include <Render/RSRender.h>

LRESULT RENDERAPI ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace rs {

    HINSTANCE g_hInstance = NULL;
    HWND g_hWnd = NULL;
    int g_iCmdShow = NULL;
    LPCWSTR Win32_WindowName = TEXT("RSEngine");

    int g_resX = 0;
    int g_resY = 0;
    char* WindowName = "RSEngine";

    LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
        //if (ImGui_ImplWin32_WndProcHandler(hwnd, msg, wParam, lParam))
        //    return true;

        switch (msg) {
        case WM_KEYDOWN:
            if (wParam == VK_ESCAPE) {
                if (MessageBox(0, L"Are you sure you want to exit?",
                    L"Really?", MB_YESNO | MB_ICONQUESTION) == IDYES)
                    DestroyWindow(hwnd);
            }
            return 0;
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        }
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }

    bool Window::Init(int w, int h) {
        // Set the resolution in a global
        g_resX = w;
        g_resY = h;

        WNDCLASSEX wc;

        wc.cbSize = sizeof(WNDCLASSEX);
        wc.style = CS_HREDRAW | CS_VREDRAW;
        wc.lpfnWndProc = WndProc;
        wc.cbClsExtra = NULL;
        wc.cbWndExtra = NULL;
        wc.hInstance = g_hInstance;
        wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
        wc.hCursor = LoadCursor(NULL, IDC_ARROW);
        wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 2);
        wc.lpszMenuName = NULL;
        wc.lpszClassName = Win32_WindowName;
        wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

        if (!RegisterClassEx(&wc)) {
            // Failed to register class.
            //std::cout << "Failed to register class.";
            return false;
        }

        g_hWnd = CreateWindowEx(NULL,
            Win32_WindowName,
            Win32_WindowName, // For now...
            WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT, CW_USEDEFAULT,
            w, h,
            NULL,
            NULL,
            g_hInstance,
            NULL);

        if (!g_hWnd) {
            // Window handler failed to initialize.
            //std::cout << "Window handler failed to initialize.";
            return false;
        }

        ShowWindow(g_hWnd, g_iCmdShow);
        UpdateWindow(g_hWnd);

        renderResX = static_cast<float>(g_resX);
        renderResY = static_cast<float>(g_resY);
        renderHwnd = g_hWnd;

        return true;
    }

} // namespace rs
