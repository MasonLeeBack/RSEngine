/*

RSEngine
Copyright (c) 2020 Mason Lee Back

File name: LevelManager.h

*/

#ifndef _LEVELMANAGER_H_
#define _LEVELMANAGER_H_

#include <Types/RSArray.h>

namespace rs {
	class LevelRoot;

	//
	// Outside of the editor, this would not be used.
	// However in certain scenarios this might be viable
	// for pre-loading maps on the fly.
	//
	class LevelManager {
	public:
		LevelManager();
		~LevelManager();

		std::shared_ptr<LevelRoot> getCurrentLevel();
		void setLevelFromIndex(int index);

	private:
		RSArray<std::shared_ptr<LevelRoot>> levelStack;
		int levelIndex = -1;
	};
}

#endif // _LEVELMANAGER_H_
