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

File name: Config.h

*/

#pragma once
#ifndef _CONFIG_H_
#define _CONFIG_H_

#include <string>

namespace rs {

    class PolyConfig {
    public:
        int ReadCommandLineInt(char key);
        std::string ReadCommandLineString(char key);

        int ReadEngineConfigInt(char key);
        std::string ReadEngineConfigString(char key);

        //User config
        bool CreateUserData(char name, char dirname);
        bool DoesUserDataExist(char name, char dirname);

    private:

    };

} // namespace rs

#endif // _Config_h_
