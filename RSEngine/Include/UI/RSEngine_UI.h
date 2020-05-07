/*

RSEngine
Copyright (c) 2020 Mason Lee Back

File name: RSEngine_UI.h

*/

#ifndef _RSENGINE_UI_H_
#define _RSENGINE_UI_H_

namespace rs::UI {

	class RareUI {
	public:
		bool Initialize();
		void Shutdown();
	};

	extern RareUI* g_rareUI;

} // namespace rs::UI

#endif // _RSENGINE_UI_H_
