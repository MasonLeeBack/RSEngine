/*

RSEngine
Copyright (c) 2020 Mason Lee Back

File name: RSRender_Shader.h

*/

#ifndef _RSRENDER_SHADER_H_
#define _RSRENDER_SHADER_H_

namespace rs::Renderer {

	enum class RSShaderType {
		RS_VERTEX_SHADER,
		RS_PIXEL_SHADER
	};

	class RSRender_Shader {
	public:
		RSRender_Shader(RSShaderType);

		void InitializeShaderFromFile(const char*);

		ID3D11VertexShader* vertexShader;
		ID3D11PixelShader* pixelShader;

		ID3D11InputLayout* inputLayout;

		virtual RSShaderType getShaderType() { return type; };
		virtual bool isInitialized() { return Initialized; };
	private:
		RSShaderType type;
		bool Initialized;
	};

} // namespace rs::Renderer

#endif // _RSRENDER_SHADER_H_
