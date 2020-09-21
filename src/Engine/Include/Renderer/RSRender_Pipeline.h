/*

RSEngine
Copyright (c) 2020 Mason Lee Back

File name: RSRender_Pipeline.h

*/

#ifndef _RSRENDER_PIPELINE_H_
#define _RSRENDER_PIPELINE_H_

#include "RSRender_Structs.h"
#include "RSRender_Shader.h"
#include "RSRender_Buffer.h"

#include <vector>

namespace rs::Renderer {

	typedef struct {
		DirectX::XMMATRIX world;
	} vsConst_PerObject;

	typedef struct psConst_PerObject {
		bool isTextured = 0;
		bool padding[15];
	} psConst_PerObject;

	typedef struct ConstantObjects {
		RSRender_Buffer* vsConstantBuffer;
		void* constantObject;
	} ConstantObjects;

	typedef struct RSRenderPipeline {
		// Vertex shader contains the input layout, which is then set
		// by the renderer.
		RSRender_Shader* VertexShader;
		RSRender_Shader* PixelShader;

		RSRender_Buffer* VertexBuffer;
		RSRender_Buffer* IndexBuffer;

		// Todo: do we really need these?
		int                 VertexCount;
		int                 IndexCount;

		// User-defined objects can use more than one constant buffer
		// for each stage, so we store them in a vector instead.
		// Currently, users can only use up to (10) constant buffers - 
		// the first four are reserved for the engine.
		std::vector<ConstantObjects> vsConstantObjects;
		std::vector<ConstantObjects> psConstantObjects;

		// This is reset every frame, however it does not need set
		// by the user unless they plan on modifying the cull state.
		RSCullState cullState = RSCullState::CullAll;

		//// LEGACY LEGACY LEGACY ////
		RSRender_Buffer* ObjectConstant;
		RSRender_Buffer* pixelConst;

		vsConst_PerObject	objectVSConst;
		psConst_PerObject   objectPSConst;
		//// LEGACY LEGACY LEGACY ////

		// Todo: replace this
		RSTexture           Texture;

		bool isGuiElement = false;
		float alpha = 1.0f;

		RSRender_Buffer* getVSConstBuffer(int index);
		RSRender_Buffer* getPSConstBuffer(int index);

		// This method is preferable, however if the user wishes
		// to use their own vertex data, they will have to
		// initialize the buffers manually using RSRender_Buffer->Initialize()
		bool createBuffersForMesh(MeshData mesh);

		void* getVSConstObject(int index);
		void* getPSConstObject(int index);

		void Draw(bool isAlphaPass = false);
	} RSRenderPipeline;

	// Pipeline helper funcs
	void CreatePipeline();
	void DrawPipeline(RSRenderPipeline* pipeline);

} // namespace rs::Renderer

#endif // _RSRENDER_PIPELINE_H_
