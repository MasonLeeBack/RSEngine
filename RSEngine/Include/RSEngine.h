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

File name: RSEngine.h

*/

#pragma once
#ifndef _RSEngine_h_
#define _RSEngine_h_

//temporary
#define RSThrowError(x) MessageBox(NULL, x, L"Error!", MB_OK);

#include <Windows.h>
#include <Xinput.h>
#include <d3dcompiler.h>
#include <d3d11.h>
#include <d3d11_1.h>
#include <DirectXMath.h>
#include <DirectXPackedVector.h>
#include <d3d9types.h>
#include <dxgi.h>
#include <comdef.h>

#include <string>
#include <string.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <map>
#include <algorithm>
#include <cctype>

#include "RSEngine_BuildMacros.h"

#include "Render\RSRender.h"

// Types
#include "Types\RareTypes.h"

// Utils
#include "Utils\RSUtils.h"

// Classes
#include "Classes\RSClasses.h"

#include "Window\WindowSystem.h"
#include "Input\RareInput.h"
#include "Core\Engine.h"
#include "Parser\RareParser.h"
#include "Core\Config.h"
#include "Core\Filesystem.h"

#include "Editor\Editor.h"
#include "Core\Console.h"
#include "Core\GameLib.h"

#endif // _RSEngine_h_
