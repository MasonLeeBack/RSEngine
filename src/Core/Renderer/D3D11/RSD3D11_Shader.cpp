/*

RSEngine
Copyright (c) 2019 Mason Lee Back

File name: RSD3D11_Shader.cpp

*/

#include <Render/D3D11/RSD3D11.h>

#ifdef _WIN32

namespace rs::Render {
    RSD3D11_Shader::RSD3D11_Shader() {
    }

    RSD3D11_Shader::RSD3D11_Shader(const RSShaderDesc& desc) : l_vertexShader(nullptr), l_geometryShader(nullptr), l_hullShader(nullptr), l_pixelShader(nullptr), l_domainShader(nullptr) {
        device = ((RSD3D11*)g_CurrentRenderer)->getDevice();
        HRESULT hr;
        switch (desc.stage) {
        case RS_SHADER_STAGE_VS: {
            hr = device->CreateVertexShader(desc.shader_data, desc.shader_size, 0, &l_vertexShader);
            break;
        }
        case RS_SHADER_STAGE_PS: {
            hr = device->CreatePixelShader(desc.shader_data, desc.shader_size, 0, &l_pixelShader);
            break;
        }
        case RS_SHADER_STAGE_DS: {
            hr = device->CreateDomainShader(desc.shader_data, desc.shader_size, 0, &l_domainShader);
            break;
        }
        case RS_SHADER_STAGE_HS: {
            hr = device->CreateHullShader(desc.shader_data, desc.shader_size, 0, &l_hullShader);
            break;
        }
        case RS_SHADER_STAGE_GS: {
            hr = device->CreateGeometryShader(desc.shader_data, desc.shader_size, 0, &l_geometryShader);
            break;
        }
        default:
            break;
        }
        if (FAILED(hr)) {
            _com_error err(hr);
            LPCTSTR errMsg = err.ErrorMessage();

            /* To do: implement error redirectory here */
        }

    }

    RSD3D11_Shader::~RSD3D11_Shader() {
        switch (stage) {
        case RS_SHADER_STAGE_VS:
            l_vertexShader->Release();
            break;
        case RS_SHADER_STAGE_GS:
            l_geometryShader->Release();
            break;
        case RS_SHADER_STAGE_HS:
            l_hullShader->Release();
            break;
        case RS_SHADER_STAGE_PS:
            l_pixelShader->Release();
            break;
        case RS_SHADER_STAGE_DS:
            l_domainShader->Release();
            break;
        default:
            break;
        }
        
    }

    RSShaderStage RSD3D11_Shader::getStage() {
        return stage;
    }

    RSShader RSD3D11_Shader::getShader() {
        switch (stage) {
        case RS_SHADER_STAGE_VS:
            return l_vertexShader;
            break;
        case RS_SHADER_STAGE_GS:
            return l_geometryShader;
            break;
        case RS_SHADER_STAGE_HS:
            return l_hullShader;
            break;
        case RS_SHADER_STAGE_PS:
            return l_pixelShader;
            break;
        case RS_SHADER_STAGE_DS:
            return l_domainShader;
            break;
        default:
            return nullptr;
            break;
        }
    }

} // namespace rs::Render

#endif _WIN32