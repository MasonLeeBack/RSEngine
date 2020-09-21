/*

RSEngine
Copyright (c) 2020 Mason Lee Back

File name: EdNodeEditor.h

*/

#ifndef _EDNODEEDITOR_H_
#define _EDNODEEDITOR_H_

namespace rs::Editor {

	class EdNodeEditor : public EditorComponent {
	public:
		void Initialize();
		void Frame();
		void Shutdown();

	private:

	};

} // namespace rs::Editor

#endif // _EDNODEEDITOR_H_
