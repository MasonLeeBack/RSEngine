/*

RSEngine
Copyright (c) 2019 Mason Lee Back

File name: RSRender_Shader.cpp

*/

#include <Renderer/RSRender.h>
#include <d3dcompiler.h>
#include <comdef.h>

namespace rs::Renderer {

	typedef std::map<const char*, ID3D11VertexShader*>  VERTEXSHADER_MAP;
	typedef std::map<const char*, ID3D11PixelShader*>   PIXELSHADER_MAP;
	typedef std::map<const char*, ID3D11InputLayout*>   INPUTLAYOUT_MAP;

	VERTEXSHADER_MAP VertexMap;
	PIXELSHADER_MAP  PixelMap;
	INPUTLAYOUT_MAP  LayoutMap;

	wchar_t* convertCharArrayToLPCWSTR(const char* charArray) {
		wchar_t* wString = new wchar_t[4096];
		MultiByteToWideChar(CP_ACP, 0, charArray, -1, wString, 4096);
		return wString;
	}

    RSRender_Shader::RSRender_Shader(RSShaderType shType, D3D11_INPUT_ELEMENT_DESC* layout, int arraySize) : type(shType),
		Initialized(false), vertexShader(nullptr), inputLayout(nullptr), pixelShader(nullptr), inputElement(layout), elementSize(arraySize)
	{
		if (shType == RSShaderType::RS_VERTEX_SHADER && layout == nullptr)
			assert(shType == RSShaderType::RS_VERTEX_SHADER && layout == nullptr);
	}

	void RSRender_Shader::InitializeShaderFromFile(const char* fileName)
	{
        DWORD shaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;

        if (type == RSShaderType::RS_PIXEL_SHADER) {
            if (PixelMap.count(fileName) <= 0) {
                HRESULT hr;

                ID3DBlob* ps_Blob;
                D3DCompileFromFile(convertCharArrayToLPCWSTR(fileName), NULL, D3D_COMPILE_STANDARD_FILE_INCLUDE, "PS", "ps_5_0", shaderFlags, NULL, &ps_Blob, NULL);

                hr = g_RSRender->l_Device->CreatePixelShader(
                    ps_Blob->GetBufferPointer(),
                    ps_Blob->GetBufferSize(),
                    nullptr,
                    &pixelShader
                );
                if (FAILED(hr)) {
                    _com_error err(hr);
                    LPCTSTR errMsg = err.ErrorMessage();
                    MessageBox(NULL, errMsg, L"CreatePixelShader error", MB_OK);
                    return;
                }

                PixelMap.insert(std::pair<const char*, ID3D11PixelShader*>(fileName, pixelShader));
            }
            else {
                pixelShader = PixelMap.find(fileName)->second;
            }
        }

        if (type == RSShaderType::RS_VERTEX_SHADER) {
            if (VertexMap.count(fileName) <= 0) {
                HRESULT hr;

                ID3DBlob* vs_Blob;
                D3DCompileFromFile(convertCharArrayToLPCWSTR(fileName), NULL, D3D_COMPILE_STANDARD_FILE_INCLUDE, "VS", "vs_5_0", shaderFlags, NULL, &vs_Blob, NULL);

                hr = g_RSRender->l_Device->CreateVertexShader(
                    vs_Blob->GetBufferPointer(),
                    vs_Blob->GetBufferSize(),
                    nullptr,
                    &vertexShader
                );
                if (FAILED(hr)) {
                    _com_error err(hr);
                    LPCTSTR errMsg = err.ErrorMessage();
                    MessageBox(NULL, errMsg, L"CreateVertexShader error", MB_OK);
                    return;
                }

                hr = g_RSRender->l_Device->CreateInputLayout(
                    inputElement,
                    elementSize,
                    vs_Blob->GetBufferPointer(),
                    vs_Blob->GetBufferSize(),
                    &inputLayout
                );
                if (FAILED(hr)) {
                    _com_error err(hr);
                    LPCTSTR errMsg = err.ErrorMessage();
                    MessageBox(NULL, errMsg, L"CreateInputLayout error", MB_OK);
                    return;
                }

                LayoutMap.insert(std::pair<const char*, ID3D11InputLayout*>(fileName, inputLayout));
                VertexMap.insert(std::pair<const char*, ID3D11VertexShader*>(fileName, vertexShader));
            }
            else {
                inputLayout = LayoutMap.find(fileName)->second;
                vertexShader = VertexMap.find(fileName)->second;
            }
        }
        Initialized = true;
	}

} // namespace rs::Renderer
