/*

RSEngine
Copyright (c) 2020 Mason Lee Back

File name: WindowSystem.h

*/

#pragma once
#ifndef _WindowSystem_h_
#define _WindowSystem_h_

namespace rs {
    struct WindowClassConfig {
        unsigned int windowWidth;
        unsigned int windowHeight;
        const char*  windowHame;
    };

    class Window {
    public:
        Window(WindowClassConfig cfg);
        ~Window();

        void* getWindowHandle();
        WindowClassConfig getWindowConfig();

    private:
        void* windowHandle;
        WindowClassConfig wCfg;
    };

} // namespace rs

#endif // _WindowSystem_h_
