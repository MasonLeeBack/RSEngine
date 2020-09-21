/*

RSEngine
Copyright (c) 2020 Mason Lee Back

File name: UIPanel.cpp

*/

#include <Classes/UIPanel.h>
#include <Renderer/RSGeometryGenerator.h>
#include <Renderer/RSRender.h>

namespace rs {
    INITIALIZE_INSTANCE_SOURCE(UIPanel);

    void UIPanel::render() {
        if (pipeline == nullptr) {
            pipeline = new RSRenderPipeline;

            GeometryGenerator gen;
            MeshData quad = gen.GenerateFullscreenQuad();

            pipeline->createBuffersForMesh(quad);

            RSBufferDesc vsConstDesc;
            vsConstDesc.mType = RSBufferType::CONST_BUFFER;
            vsConstDesc.mElementCount = 1;
            vsConstDesc.mStride = sizeof(vsConst_PerObject);

            pipeline->ObjectConstant = new RSRender_Buffer(vsConstDesc);
            pipeline->ObjectConstant->Initialize(&pipeline->objectVSConst);

            RSBufferDesc psConstDesc;
            psConstDesc.mType = RSBufferType::CONST_BUFFER;
            psConstDesc.mElementCount = 1;
            psConstDesc.mStride = sizeof(psConst_PerObject);

            pipeline->pixelConst = new RSRender_Buffer(psConstDesc);
            pipeline->pixelConst->Initialize(&pipeline->objectPSConst);

            pipeline->VertexShader = new RSRender_Shader(RSShaderType::RS_VERTEX_SHADER);
            pipeline->VertexShader->InitializeShaderFromFile("data/shaders/shader_ui_vs.hlsl");

            pipeline->PixelShader = new RSRender_Shader(RSShaderType::RS_PIXEL_SHADER);
            pipeline->PixelShader->InitializeShaderFromFile("data/shaders/shader_ui_ps.hlsl");
        }

        Vector2 res = renderResolution;

        float aspect = res.X / res.Y;

        DirectX::XMMATRIX worldMatrix;
        
        // wow this is ugly
        worldMatrix = DirectX::XMMatrixScaling((((1 / (res.X)) * (Size.Offset_X))*aspect)+Size.Scale_X*aspect*2, ((1/res.Y)*(Size.Offset_Y))+Size.Scale_Y*2 , 1);
        worldMatrix *= DirectX::XMMatrixRotationZ(DirectX::XMConvertToRadians(Rotation*-1));
        worldMatrix *= DirectX::XMMatrixTranslation(((1/res.X)*(((Position.Offset_X*2)-res.X)+Size.Offset_X)*aspect)+Position.Scale_X*aspect*2, ((1 / res.Y) * (((Position.Offset_Y * 2) - res.Y) + Size.Offset_Y) *-1)+Position.Scale_Y*-1*2, 1);

        pipeline->objectVSConst.world = DirectX::XMMatrixTranspose(worldMatrix);
        pipeline->objectPSConst.isTextured = pipeline->Texture.DrawTexture;

        //pipeline->ObjectConstant->Update(&pipeline->objectVSConst);
        //pipeline->pixelConst->Update(&pipeline->objectPSConst);

        g_RSRender->l_DeviceContext->UpdateSubresource(pipeline->pixelConst->mpGPUData, 0, NULL, &pipeline->objectPSConst, 0, 0);
        g_RSRender->l_DeviceContext->UpdateSubresource(pipeline->ObjectConstant->mpGPUData, 0, NULL, &pipeline->objectVSConst, 0, 0);

        pipeline->alpha = Transparency;

        pipeline->Draw();

        renderChildren();
    }

} // namespace rs
