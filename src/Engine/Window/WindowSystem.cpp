/*

RSEngine
Copyright (c) 2020 Mason Lee Back

File name: WindowSystem.cpp

*/

#include <iostream>

#include <Window/WindowSystem.h>
#include <Renderer/RSRender.h>
using namespace rs::Renderer;
#include <Window/resource.h>

extern LRESULT  ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace rs {

    LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
        if (ImGui_ImplWin32_WndProcHandler(hwnd, msg, wParam, lParam))
            return true;

        static bool s_in_sizemove = false;
        static bool s_minimized = false;

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
        case WM_SIZE:
            if (wParam == SIZE_MINIMIZED)
            {
                // The window was minimized (you should probably suspend the application)
                if (!s_minimized)
                {
                    s_minimized = true;
                }
            }
            else if (s_minimized)
            {
                // The window was minimized and is now restored (resume from suspend)
                s_minimized = false;
            }
            else if (!s_in_sizemove)
            {

            }
            break;

        case WM_ENTERSIZEMOVE:
            // We want to avoid trying to resizing the swapchain as the user does the 'rubber band' resize
            s_in_sizemove = true;
            break;

        case WM_EXITSIZEMOVE:
            s_in_sizemove = false;
            // Here is the other place where you handle the swapchain resize after the user stops using the 'rubber-band' 
            tagRECT rect;
            if (GetClientRect(hwnd, &rect))
            {
                int width = rect.right - rect.left;
                int height = rect.bottom - rect.top;

                g_RSRender->UpdateSwapChainResolution(Vector2(static_cast<float>(width), static_cast<float>(height)));
            }
            break;

        case WM_GETMINMAXINFO:
        {
            // We want to prevent the window from being set too tiny
            auto info = reinterpret_cast<MINMAXINFO*>(lParam);
            info->ptMinTrackSize.x = 800;
            info->ptMinTrackSize.y = 600;
        }
        break;
        }
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }

    wchar_t* charConvertLPCWSTR(const char* charArray)
    {
        size_t strLen = strlen(charArray) + 9;
        wchar_t* wString = new wchar_t[strLen];
        MultiByteToWideChar(CP_ACP, 0, charArray, -1, wString, static_cast<int>(strLen));
        return wString;
    }

    // Win32 implementation of WindowSystem
    Window::Window(WindowClassConfig cfg) : windowHandle(nullptr)
    {
        HINSTANCE g_hInstance = GetModuleHandle(NULL);
        LPCWSTR windowName = charConvertLPCWSTR(cfg.windowHame);

        // Assign window configuration to this class
        wCfg = cfg;

        WNDCLASSEX wc;

        wc.cbSize = sizeof(WNDCLASSEX);
        wc.style = CS_HREDRAW | CS_VREDRAW;
        wc.lpfnWndProc = WndProc;
        wc.cbClsExtra = NULL;
        wc.cbWndExtra = NULL;
        wc.hInstance = g_hInstance;
        wc.hIcon = LoadIcon(g_hInstance, MAKEINTRESOURCE(IDI_ICON1));
        wc.hCursor = LoadCursor(NULL, IDC_ARROW);
        wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
        wc.lpszMenuName = NULL;
        wc.lpszClassName = windowName;
        wc.hIconSm = LoadIcon(g_hInstance, MAKEINTRESOURCE(IDI_ICON1));

        if (!RegisterClassEx(&wc)) {
            // Failed to register class.
            std::cout << "Failed to register class.";
            return;
        }

        RECT rect;
        rect.left = rect.top = 0;
        rect.right = cfg.windowWidth;
        rect.bottom = cfg.windowHeight;
        ::AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

        windowHandle = CreateWindowEx(NULL,
            windowName,
            windowName, // For now...
            WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT, CW_USEDEFAULT,
            rect.right - rect.left, rect.bottom - rect.top,
            NULL,
            NULL,
            g_hInstance,
            NULL);



        if (!windowHandle) {
            // Window handler failed to initialize.
            std::cout << "Window handler failed to initialize.";
            return;
        }

        ShowWindow((HWND)windowHandle, 1);
        UpdateWindow((HWND)windowHandle);

        return;
    }

    Window::~Window()
    {
    }

    void* Window::getWindowHandle()
    {
        return windowHandle;
    }

    WindowClassConfig Window::getWindowConfig()
    {
        return wCfg;
    }

} // namespace rs
