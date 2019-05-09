/*

RSEngine
Copyright (c) 2019 Mason Lee Back

File name: RSRender_Shader.cpp

*/

#include <RSEngine.h>

namespace rs::Render {
    RSRender_Shader::~RSRender_Shader()
    {
    }
    RSShaderStage RSRender_Shader::getStage()
    {
        return stage;
    }
} // namespace rs::Render