/*

RSEngine
Copyright (c) 2019 Mason Lee Back

File name: RSD3D11_Shader.h

*/

#ifndef _RSD3D11_Shader_h_
#define _RSD3D11_Shader_h_

namespace rs::Render {
    class RSD3D11_Shader : public RSRender_Shader {
    public:
        RSD3D11_Shader();
        RSD3D11_Shader(const RSShaderDesc& desc);
        ~RSD3D11_Shader();

        RSShaderStage getStage() override;
        RSShader getShader() override;

    private:
        RSShaderStage stage;

        ID3D11VertexShader* l_vertexShader;
        ID3D11HullShader* l_hullShader;
        ID3D11PixelShader* l_pixelShader;
        ID3D11GeometryShader* l_geometryShader;
        ID3D11DomainShader* l_domainShader;

        ID3D11Device* device;
    };

} // rs::Render

#endif // _RSD3D11_Shader_h_
