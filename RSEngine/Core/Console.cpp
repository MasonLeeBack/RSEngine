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

File name: Console.cpp

*/

#include <Core/Console.h>

namespace rs {
    Console* g_Console;
    bool EditorEnabled = true; 	// At this revision, the editor is the only option until the client is finished.
    
    bool Console::Initialize() {
        return true;
    }
    
    const char* Console::ParseCommand(const char* command) {
        return "Parsed like the slave I am";
    }
    
    void Console::Shutdown() {
    
    }

    bool Console::addVar(const char* name, cvar* conVar)
    {
        rConsoleVars* place_var = new rConsoleVars;
        for (auto v : console_vars) {
            if (name == v->cvarName) {
                return false;
            }
        }

        place_var->cvarName = name;
        place_var->conVar = conVar;

        console_vars.push_back(place_var);

        return true;
    }
    
} // namespace rs
