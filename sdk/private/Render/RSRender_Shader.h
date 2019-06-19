/*

RSEngine
Copyright (c) 2019 Mason Lee Back

File name: RSRender_Shader.h

*/

#pragma once
#ifndef _RSRender_Shader_h_
#define _RSRender_Shader_h_

namespace rs::Render {
    class RSRender_Shader {
    public:
        RSRender_Shader();
        RSRender_Shader(const RSShaderDesc& desc);
        ~RSRender_Shader();

        virtual RSShaderStage getStage();
        virtual RSShader getShader();

    private:
        RSShaderStage stage;
    };

} // namespace rs::Render

#endif // _RSRender_Shader_h_
