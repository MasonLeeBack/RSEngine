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

File name: EdConsole.h

*/

#pragma once
#ifndef _EdConsole_h_
#define _EdConsole_h_

#include <Editor/EditorComponent.h>
#include <Classes/RSClasses.h>

namespace rs {
    namespace Editor {
        class EConsole : public EditorComponent {
            char                  InputBuf[256];
            ImVector<char*>       Items;
            ImVector<const char*> Commands;
            ImVector<char*>       History;
            int                   HistoryPos;    // -1: new line, 0..History.Size-1 browsing history.
            ImGuiTextFilter       Filter;
            bool                  AutoScroll;
            bool                  ScrollToBottom;
        public:
            bool Initialize();
            int TextEditCallback(ImGuiInputTextCallbackData* data);
            void ExecCommand(const char* command_line);
            void AddLog(const char* fmt, ...) IM_FMTARGS(2);
            void ClearLog();
            void Draw(bool* p_open);
        };
    }

} // namespace rs

#endif // _EdConsole_h_
