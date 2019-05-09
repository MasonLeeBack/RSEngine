/*

RSEngine
Copyright (c) 2019 Mason Lee Back

File name: RSD3D11_Shader.h

*/

#ifndef _RSD3D11_Shader_h_
#define _RSD3D11_Shader_h_

namespace rs::Render {
    class RSD3D11_Shader : public RSRender_Shader {
        RSD3D11_Shader();
        RSD3D11_Shader(const RSShaderDesc& desc);
        ~RSD3D11_Shader();

        RSShaderStage getStage() override;

    private:
        RSShaderStage stage;
    };

} // rs::Render

#endif // _RSD3D11_Shader_h_
