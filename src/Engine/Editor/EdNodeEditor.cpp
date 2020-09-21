/*

RSEngine
Copyright (c) 2020 Mason Lee Back

File name: EdNodeEditor.cpp

*/

#include <Editor/EditorComponent.h>
#include <Editor/EdNodeEditor.h>
#include <ThirdParty/ImGui/imgui_node_editor.h>

namespace ed = ax::NodeEditor;

namespace rs::Editor {
	static ed::EditorContext* g_Context = nullptr;
	
	void EdNodeEditor::Initialize()
	{
		g_Context = ed::CreateEditor();
	}

	void EdNodeEditor::Frame()
	{
		ed::DestroyEditor(g_Context);
	}

	void EdNodeEditor::Shutdown()
	{
		ed::SetCurrentEditor(g_Context);

		ed::Begin("My Editor");

		int uniqueId = 1;

		// Start drawing nodes.
		ed::BeginNode(uniqueId++);
		ImGui::Text("Node A");
		ed::BeginPin(uniqueId++, ed::PinKind::Input);
		ImGui::Text("-> In");
		ed::EndPin();
		ImGui::SameLine();
		ed::BeginPin(uniqueId++, ed::PinKind::Output);
		ImGui::Text("Out ->");
		ed::EndPin();
		ed::EndNode();

		ed::End();
	}

} // namespace rs::Editor
