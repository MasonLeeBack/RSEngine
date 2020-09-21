/*

RSEngine
Copyright (c) 2020 Mason Lee Back

File name: EdClassHelper.h

*/

#include <Editor/EdClassHelper.h>
#include <Renderer/RSRender.h>

namespace rs {
	namespace Editor {
		std::vector<EditorClassHelper*> classVector;

		void InstancePropertyEditor(std::shared_ptr<Instance> instInstance) {
			ImGui::InputText("Instance Name", &instInstance->Name);
			ImGui::Separator();
		}

		void BasePartPropertyEditor(std::shared_ptr<Instance> basePartInstance) {
			InstancePropertyEditor(basePartInstance);
			std::shared_ptr<BasePart> mBasePartInstance = std::dynamic_pointer_cast<BasePart>(basePartInstance);
			bool physicsEnabled = mBasePartInstance->PhysicsEnabled;
			ImGui::Checkbox("Physics enabled", &physicsEnabled);
			mBasePartInstance->setPhysicsEnabled(physicsEnabled);
			ImGui::DragFloat("Opacity", &mBasePartInstance->Opacity);
			Vector3* partVelocity = &mBasePartInstance->Velocity;
			float* floatv[3] = { &partVelocity->X, &partVelocity->Y, &partVelocity->Z };
			if (ImGui::DragFloat3("Velocity", *floatv, 1, 0, 0, "%.3f")) {
				mBasePartInstance->setVelocity(*partVelocity);
			}
			ImGui::Separator();
			Vector3* partSize = &mBasePartInstance->Size;
			float* floats[3] = { &partSize->X, &partSize->Y, &partSize->Z };
			ImGui::DragFloat3("Size", *floats, 1, 0, 0, "%.3f");
			Vector3* partPosition = &mBasePartInstance->Position;
			float* floatp[3] = { &partPosition->X, &partPosition->Y, &partPosition->Z };
			if (ImGui::DragFloat3("Position", *floatp, 1, 0, 0, "%.3f"))
			{
				mBasePartInstance->setPosition(*partPosition);
			};
			Vector3* partRotation = &mBasePartInstance->Rotation;
			float* floatr[3] = { &partRotation->X, &partRotation->Y, &partRotation->Z };
			ImGui::DragFloat3("Rotation", *floatr, 1, 0, 0, "%.3f");
			ImGui::Separator();
		}

		void PartPropertyEditor(std::shared_ptr<Instance> partInstance) {
			BasePartPropertyEditor(partInstance);
			std::shared_ptr<Part> mPartInstance = std::dynamic_pointer_cast<Part>(partInstance);
		}

		void MeshPartPropertyEditor(std::shared_ptr<Instance> meshPartInstance) {
			BasePartPropertyEditor(meshPartInstance);
			std::shared_ptr<MeshPart> mMeshPartInstance = std::dynamic_pointer_cast<MeshPart>(meshPartInstance);
			ImGui::InputText("Mesh name", &mMeshPartInstance->MeshFile);
			ImGui::InputText("Mesh texture", &mMeshPartInstance->MeshTexture);
			ImGui::Separator();
		}

		void TexturePropertyEditor(std::shared_ptr<Instance> textureInstance) {
			InstancePropertyEditor(textureInstance);
			std::shared_ptr<Texture> mTextureInstance = std::dynamic_pointer_cast<Texture>(textureInstance);
			ImGui::InputText("File", &mTextureInstance->File);
		}

		void CameraPropertyEditor(std::shared_ptr<Instance> cameraInstance) {
			InstancePropertyEditor(cameraInstance);
			std::shared_ptr<Camera> mCameraInstance = std::dynamic_pointer_cast<Camera>(cameraInstance);
			Vector3* cameraEyePos = &mCameraInstance->EyePos;
			float* floatep[3] = { &cameraEyePos->X, &cameraEyePos->Y, &cameraEyePos->Z };
			ImGui::DragFloat3("Eye Position", *floatep, 1, 0, 0, "%.3f");
			Vector3* cameraLookAtPos = &mCameraInstance->LookAtPos;
			float* floatlap[3] = { &cameraLookAtPos->X, &cameraLookAtPos->Y, &cameraLookAtPos->Z };
			ImGui::DragFloat3("Look At Position", *floatlap, 1, 0, 0, "%.3f");
			Vector3* cameraUpVector = &mCameraInstance->UpVector;
			float* floatuv[3] = { &cameraUpVector->X, &cameraUpVector->Y, &cameraUpVector->Z };
			ImGui::DragFloat3("Up Vector", *floatuv, 1, 0, 0, "%.3f");
			ImGui::Separator();
			ImGui::DragFloat("Field of View", &mCameraInstance->FieldOfView, 1, 0, 0, "%1f", 1);
			ImGui::Separator();
			Vector2* viewportSize = &mCameraInstance->ViewportSize;
			float* floatvps[2] = { &viewportSize->X, &viewportSize->Y };
			ImGui::DragFloat2("Viewport size", *floatvps, 0, 0, 0, "", 1);
			ImGui::Separator();
		}

		void UIPanelPropertyEditor(std::shared_ptr<Instance> uiPanelInstance) {
			InstancePropertyEditor(uiPanelInstance);
			std::shared_ptr<UIPanel> mUiPanelInstance = std::dynamic_pointer_cast<UIPanel>(uiPanelInstance);

			UIScale* uiPanelPosition = &mUiPanelInstance->Position;
			float* floatpos[4] = { &uiPanelPosition->Scale_X, &uiPanelPosition->Offset_X, &uiPanelPosition->Scale_Y, &uiPanelPosition->Offset_Y };
			ImGui::DragFloat4("Position", *floatpos, 1, 0, 0, "%.3f");
			//Vector2* uiPanelPosition = &mUiPanelInstance->Position;
			//float* floatpos[2] = { &uiPanelPosition->X, &uiPanelPosition->Y };
			//ImGui::DragFloat2("Position", *floatpos, 1, 0, 0, "%.3f");

			//Vector2* uiPanelSize = &mUiPanelInstance->Size;
			//float* floatsiz[2] = { &uiPanelSize->X, &uiPanelSize->Y };
			//ImGui::DragFloat2("Size", *floatsiz, 1, 0, 0, "%.3f");
			ImGui::DragFloat("Transparency", &mUiPanelInstance->Transparency);
			ImGui::DragFloat("Rotation", &mUiPanelInstance->Rotation);
		}

		void UIPanelNew(void) {
			NewInstance(Panel, UIPanel);
		}

		void ClassHelper_Initialize() {
			EditorClassHelper* partClassHelper = new EditorClassHelper;
			partClassHelper->ClassName = "Part";
			partClassHelper->drawFunc = PartPropertyEditor;

			classVector.push_back(partClassHelper);

			EditorClassHelper* meshPartClassHelper = new EditorClassHelper;
			meshPartClassHelper->ClassName = "MeshPart";
			meshPartClassHelper->drawFunc = MeshPartPropertyEditor;

			classVector.push_back(meshPartClassHelper);

			EditorClassHelper* textureClassHelper = new EditorClassHelper;
			textureClassHelper->ClassName = "Texture";
			textureClassHelper->drawFunc = TexturePropertyEditor;

			classVector.push_back(textureClassHelper);

			EditorClassHelper* cameraClassHelper = new EditorClassHelper;
			cameraClassHelper->ClassName = "Camera";
			cameraClassHelper->drawFunc = CameraPropertyEditor;

			classVector.push_back(cameraClassHelper);

			EditorClassHelper* uiPanelClassHelper = new EditorClassHelper;
			uiPanelClassHelper->ClassName = "UIPanel";
			uiPanelClassHelper->drawFunc = UIPanelPropertyEditor;
			uiPanelClassHelper->canCreate = true;
			uiPanelClassHelper->newFunc = UIPanelNew;

			classVector.push_back(uiPanelClassHelper);
		}
	}
}
