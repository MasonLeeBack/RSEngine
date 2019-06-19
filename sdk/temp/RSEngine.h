/*

RSEngine
Copyright (c) 2019 Mason Lee Back

File name: RSEngine.h

*/

#pragma once
#ifndef _RSEngine_h_
#define _RSEngine_h_

//temporary
#define RSThrowError(x) MessageBox(NULL, x, L"Error!", MB_OK);

#include <string>
#include <string.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <map>
#include <algorithm>
#include <cctype>

#include "Render\RSRender.h"

// Types
#include "Types\RareTypes.h"

// Utils
#include "Utils\RSUtils.h"

// Classes
#include "Classes\RSClasses.h"
#include "Input\RareInput.h"
#include "Core\Engine.h"
#include "Parser\RareParser.h"
#include "Core\Config.h"
#include "Core\Filesystem.h"
#include "Core\Console.h"
#include "Core\GameLib.h"

#endif // _RSEngine_h_
