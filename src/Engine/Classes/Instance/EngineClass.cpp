/*

RSEngine
Copyright (c) 2020 Mason Lee Back

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

