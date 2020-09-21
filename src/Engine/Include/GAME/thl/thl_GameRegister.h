/*

thl game
Copyright (c) 2020 Mason Lee Back

File name: thl_GameRegister.h

*/

#ifndef _THL_GAMEREGISTER_H_
#define _THL_GAMEREGISTER_H_

namespace thl {
	class GameRegister {
	public:
		bool Initialize();
		void Update();
		void Shutdown();
	private:
		void InitializeClassesForEditor();
		void InitializeClassesForEngine();
	};
}

#endif //_THL_GAMEREGISTER_H_
