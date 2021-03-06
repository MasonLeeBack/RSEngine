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

File name: Console.h

*/

#pragma once
#ifndef _Console_h_
#define _Console_h_

#include <vector>

namespace rs {
    typedef enum {
        cvar_type_undefined,
        cvar_type_int,
        cvar_type_float,
        cvar_type_bool
    }cvar_type;

    typedef struct {
        cvar_type cvarType;
        void* convar;
    }cvar;

    typedef struct {


    }rConsoleCommands;

    typedef struct {
        const char* cvarName;
        cvar* conVar;
    }rConsoleVars;

    class Console {
    public:
        bool Initialize();
        const char* ParseCommand(const char* command);
        void Shutdown();

        bool addCommand(const char* name, void* consoleCommand);
        bool addVar(const char* name, cvar* conVar);

    private:
        std::vector<rConsoleCommands*> console_commands;
        std::vector<rConsoleVars*> console_vars;
    };

    extern Console* g_Console;

} // namespace rs

#endif // _Console_h_
