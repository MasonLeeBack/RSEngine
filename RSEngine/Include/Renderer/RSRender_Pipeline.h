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

namespace rs::Renderer {

	typedef struct {
		DirectX::XMMATRIX world;
	} regB1;

	typedef struct {
		// Vertex shader contains the input layout, which is then set
		// by the renderer.
		RSRender_Shader* VertexShader;
		RSRender_Shader* PixelShader;

		RSRender_Buffer* VertexBuffer;
		RSRender_Buffer* IndexBuffer;

		RSRender_Buffer* ObjectConstant;

		regB1				bufferTest;

		RSTexture           Texture;

		int                 VertexCount;
		int                 IndexCount;
	} RSRenderPipeline;

} // namespace rs::Renderer

#endif // _RSRENDER_PIPELINE_H_
