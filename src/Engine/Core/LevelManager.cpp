/*

RSEngine
Copyright (c) 2020 Mason Lee Back

File name: LevelManager.cpp

*/

#include <Core/LevelManager.h>

namespace rs {
	LevelManager::LevelManager()
	{
	}

	LevelManager::~LevelManager()
	{
	}

	std::shared_ptr<LevelRoot> LevelManager::getCurrentLevel()
	{
		return std::shared_ptr<LevelRoot>();
	}

	void LevelManager::setLevelFromIndex(int index)
	{
		if (levelStack.get(index) == NULL) {
			
			return;
		}
	}

} // namespace rs
