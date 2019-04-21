/*

RSEngine
Copyright (c) 2019 Mason Lee Back

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

File name: RenderInstance.cpp

*/

#include <RSEngine.h>

namespace rs {
    VERTEXSHADER_MAP    VertexMap;
    PIXELSHADER_MAP     PixelMap;
    INPUTLAYOUT_MAP     LayoutMap;

    wchar_t *convertCharArrayToLPCWSTR(const char* charArray) {
        wchar_t* wString = new wchar_t[4096];
        MultiByteToWideChar(CP_ACP, 0, charArray, -1, wString, 4096);
        return wString;
    }

    bool Render::LoadShader(SHADER_TYPE shaderType, RenderPipeline* pipeline, const char* filename) {
        DWORD shaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;

        if (shaderType == ST_PixelShader) {
            if (PixelMap.count(filename) <= 0) {
                ID3D11PixelShader* PixShader;
                HRESULT hr;

                ID3DBlob* ps_Blob;
                D3DCompileFromFile(convertCharArrayToLPCWSTR(filename), NULL, D3D_COMPILE_STANDARD_FILE_INCLUDE, "PS", "ps_5_0", shaderFlags, NULL, &ps_Blob, NULL);

                hr = pdx_Device->CreatePixelShader(
                    ps_Blob->GetBufferPointer(),
                    ps_Blob->GetBufferSize(),
                    nullptr,
                    &PixShader
                );
                if (FAILED(hr)) {
                    _com_error err(hr);
                    LPCTSTR errMsg = err.ErrorMessage();
                    MessageBox(NULL, errMsg, L"Error", MB_OK);
                    return false;
                }

                PixelMap.insert(std::pair<const char*, ID3D11PixelShader*>(filename, PixShader));
                pipeline->PixelShader = PixShader;
            }
            else {
                pipeline->PixelShader = PixelMap.find(filename)->second;
            }
        }

        if (shaderType == ST_VertexShader) {
            if (VertexMap.count(filename) <= 0) {
                ID3D11VertexShader* VtxShader;
                HRESULT hr;

                ID3DBlob* vs_Blob;
                D3DCompileFromFile(convertCharArrayToLPCWSTR(filename), NULL, D3D_COMPILE_STANDARD_FILE_INCLUDE, "VS", "vs_5_0", shaderFlags, NULL, &vs_Blob, NULL);

                hr = pdx_Device->CreateVertexShader(
                    vs_Blob->GetBufferPointer(),
                    vs_Blob->GetBufferSize(),
                    nullptr,
                    &VtxShader
                );
                if (FAILED(hr)) {
                    _com_error err(hr);
                    LPCTSTR errMsg = err.ErrorMessage();
                    MessageBox(NULL, errMsg, L"Error", MB_OK);
                    return false;
                }

                ID3D11InputLayout* InputLayout;

                // This should not be defined here. But keep it for right now.
                D3D11_INPUT_ELEMENT_DESC layoutDesc[] = {
                    {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
                    {"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
                    { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
                };

                hr = pdx_Device->CreateInputLayout(
                    layoutDesc,
                    _ARRAYSIZE(layoutDesc),
                    vs_Blob->GetBufferPointer(),
                    vs_Blob->GetBufferSize(),
                    &InputLayout
                );
                if (FAILED(hr)) {
                    _com_error err(hr);
                    LPCTSTR errMsg = err.ErrorMessage();
                    MessageBox(NULL, errMsg, L"Error", MB_OK);
                    return false;
                }

                LayoutMap.insert(std::pair<const char*, ID3D11InputLayout*>(filename, InputLayout));
                pipeline->InputLayout = InputLayout;

                VertexMap.insert(std::pair<const char*, ID3D11VertexShader*>(filename, VtxShader));
                pipeline->VertexShader = VtxShader;
            }
            else {
                pipeline->InputLayout = LayoutMap.find(filename)->second;
                pipeline->VertexShader = VertexMap.find(filename)->second;
            }
        }

        return true;
    }

} // namespace rs
