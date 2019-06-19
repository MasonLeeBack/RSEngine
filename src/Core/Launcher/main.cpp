
#include <windows.h>

typedef int(*LauncherMain_t)(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    LPSTR lpCmdLine, int nCmdShow);

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    HINSTANCE launcher = LoadLibrary("Engine.dll"); // STEAM OK ... filesystem not mounted yet
    if (!launcher)
    {
        MessageBox(NULL, "Failed to load Engine DLL", "Error!", MB_OK);
        return 0;
    }

    LauncherMain_t main = (LauncherMain_t)GetProcAddress(launcher, "LauncherMain");
    return main(hInstance, hPrevInstance, lpCmdLine, nCmdShow);
}

