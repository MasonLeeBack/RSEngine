/*

RSEngine
Copyright (c) 2020 Mason Lee Back

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
