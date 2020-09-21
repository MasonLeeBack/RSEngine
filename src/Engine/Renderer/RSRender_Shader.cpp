/*

RSEngine
Copyright (c) 2020 Mason Lee Back

File name: RSRender_Shader.cpp

*/

#include <Renderer/RSRender.h>
#include <d3dcompiler.h>
#include <comdef.h>
#include <Types/RSArray.h>

#include <map>

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

    RSRender_Shader::RSRender_Shader(RSShaderType shType) : type(shType),
		Initialized(false), vertexShader(nullptr), inputLayout(nullptr), pixelShader(nullptr)
	{
	}

    HRESULT CreateInputLayoutDescFromVertexShaderSignature(ID3DBlob* pShaderBlob, ID3D11Device* pD3DDevice, ID3D11InputLayout** pInputLayout)
    {
        // Reflect shader info
        ID3D11ShaderReflection* pVertexShaderReflection = NULL;
        if (FAILED(D3DReflect(pShaderBlob->GetBufferPointer(), pShaderBlob->GetBufferSize(), IID_ID3D11ShaderReflection, (void**)&pVertexShaderReflection)))
        {
            return S_FALSE;
        }

        // Get shader info
        D3D11_SHADER_DESC shaderDesc;
        pVertexShaderReflection->GetDesc(&shaderDesc);

        // Read input layout description from shader info
        RSArray<D3D11_INPUT_ELEMENT_DESC> inputLayoutDesc;
        for (unsigned int i = 0; i < shaderDesc.InputParameters; i++)
        {
            D3D11_SIGNATURE_PARAMETER_DESC paramDesc;
            pVertexShaderReflection->GetInputParameterDesc(i, &paramDesc);

            // fill out input element desc
            D3D11_INPUT_ELEMENT_DESC elementDesc;
            elementDesc.SemanticName = paramDesc.SemanticName;
            elementDesc.SemanticIndex = paramDesc.SemanticIndex;
            elementDesc.InputSlot = 0;
            elementDesc.AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
            elementDesc.InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
            elementDesc.InstanceDataStepRate = 0;

            // determine DXGI format
            if (paramDesc.Mask == 1)
            {
                if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32) elementDesc.Format = DXGI_FORMAT_R32_UINT;
                else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32) elementDesc.Format = DXGI_FORMAT_R32_SINT;
                else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) elementDesc.Format = DXGI_FORMAT_R32_FLOAT;
            }
            else if (paramDesc.Mask <= 3)
            {
                if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32) elementDesc.Format = DXGI_FORMAT_R32G32_UINT;
                else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32) elementDesc.Format = DXGI_FORMAT_R32G32_SINT;
                else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) elementDesc.Format = DXGI_FORMAT_R32G32_FLOAT;
            }
            else if (paramDesc.Mask <= 7)
            {
                if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32) elementDesc.Format = DXGI_FORMAT_R32G32B32_UINT;
                else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32) elementDesc.Format = DXGI_FORMAT_R32G32B32_SINT;
                else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) elementDesc.Format = DXGI_FORMAT_R32G32B32_FLOAT;
            }
            else if (paramDesc.Mask <= 15)
            {
                if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_UINT32) elementDesc.Format = DXGI_FORMAT_R32G32B32A32_UINT;
                else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_SINT32) elementDesc.Format = DXGI_FORMAT_R32G32B32A32_SINT;
                else if (paramDesc.ComponentType == D3D_REGISTER_COMPONENT_FLOAT32) elementDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
            }

            //save element desc
            inputLayoutDesc.push(elementDesc);
        }

        // Try to create Input Layout
        HRESULT hr = pD3DDevice->CreateInputLayout(inputLayoutDesc.ptr(), inputLayoutDesc.size(), pShaderBlob->GetBufferPointer(), pShaderBlob->GetBufferSize(), pInputLayout);

        //Free allocation shader reflection memory
        pVertexShaderReflection->Release();
        return hr;
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

                CreateInputLayoutDescFromVertexShaderSignature(vs_Blob, g_RSRender->l_Device, &inputLayout);

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
