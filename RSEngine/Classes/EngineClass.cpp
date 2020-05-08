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

File name: Engine.cpp

*/

#include <Classes/EngineClass.h>
#include <Classes/LevelRoot.h>

namespace rs {
    INITIALIZE_INSTANCE_SOURCE(Engine);

    std::shared_ptr<LevelRoot> currentLevelRoot;
    std::vector<std::shared_ptr<LevelRoot>> levels;
    extern std::shared_ptr<Engine> eng;

    void Engine::render()
    {
        // Do some recursive checks on the engine root to make sure that the level root is placed there
        currentLevelRoot->render();
        // We don't render children
    }

} // namespace rs

