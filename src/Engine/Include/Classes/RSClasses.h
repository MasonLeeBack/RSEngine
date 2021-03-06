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

File name: RSClasses.h

*/

#pragma once
#ifndef _RSClasses_h_
#define _RSClasses_h_

#include <Types/Vector3.h>
#include <Types/Vector2.h>

#include "Instance.h"
#include "LevelRoot.h"
#include "EngineClass.h"
#include "Camera.h"
#include "BasePart.h"
#include "Part.h"
#include "MeshPart.h"
#include "Skybox.h"
#include "Folder.h"
#include "Texture.h"
#include "SceneLighting.h"
#include "UIPanel.h"

namespace rs {

    extern std::shared_ptr<LevelRoot> currentLevelRoot;
    extern std::vector<std::shared_ptr<LevelRoot>> levels;

#define NewInstance(name, type) std::shared_ptr<type> name = type::newInstance(currentLevelRoot);

extern std::shared_ptr<Engine> eng;

} // namespace rs

#endif // _RSClasses_h_
