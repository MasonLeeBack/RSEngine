/*

RSEngine
Copyright (c) 2019 Mason Lee Back

File name: RSRender_Shader.cpp

*/

#include <Render/RSRender.h>

namespace rs::Render {
    RSRender_Shader::RSRender_Shader()
    {
    }
    RSRender_Shader::RSRender_Shader(const RSShaderDesc & desc)
    {
    }
    RSRender_Shader::~RSRender_Shader()
    {
    }
    RSShaderStage RSRender_Shader::getStage()
    {
        return stage;
    }

    RSShader RSRender_Shader::getShader() {
        return nullptr;
    }
} // namespace rs::Render