/*

RSEngine
Copyright (c) 2019 Mason Lee Back

File name: EdClassHelper.h

*/

#pragma once
#ifndef _EdClassHelper_h_
#define _EdClassHelper_h_

#include <Editor/EditorComponent.h>
#include <Classes/RSClasses.h>

namespace rs {
	namespace Editor {
        struct EditorClassHelper {
            std::string ClassName;
            void (*drawFunc)(std::shared_ptr<Instance>);
        };

        extern std::vector<EditorClassHelper*> classVector;

        void ClassHelper_Initialize();
        void ClassHelper_Shutdown();
	}

} // namespace rs

#endif // _EdClassHelper_h_
