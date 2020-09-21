/*

RSEngine
Copyright (c) 2020 Mason Lee Back

File name: Part.cpp

*/

#include <Classes/Part.h>
#include <Renderer/RSRender.h>
#include <Renderer/RSGeometryGenerator.h>

namespace rs {
    INITIALIZE_INSTANCE_SOURCE(Part);

    void Part::render() {

        if (pipeline == nullptr) {
            pipeline = new RSRenderPipeline;

            GeometryGenerator gen;
            MeshData partMesh = gen.GenerateCube();

            pipeline->createBuffersForMesh(partMesh);

            //memset(&pipeline->objectVSConst, 0, sizeof(vsConst_PerObject));

            RSBufferDesc vsConstDesc;
            vsConstDesc.mType = RSBufferType::CONST_BUFFER;
            vsConstDesc.mElementCount = 1;
            vsConstDesc.mStride = sizeof(vsConst_PerObject);

            pipeline->ObjectConstant = new RSRender_Buffer(vsConstDesc);
            pipeline->ObjectConstant->Initialize(&pipeline->objectVSConst);
            
            //memset(&pipeline->objectPSConst, 0, sizeof(psConst_PerObject));

            RSBufferDesc psConstDesc;
            psConstDesc.mType = RSBufferType::CONST_BUFFER;
            psConstDesc.mElementCount = 1;
            psConstDesc.mStride = sizeof(psConst_PerObject);

            pipeline->pixelConst = new RSRender_Buffer(psConstDesc);
            pipeline->pixelConst->Initialize(&pipeline->objectPSConst);

            pipeline->VertexShader = new RSRender_Shader(RSShaderType::RS_VERTEX_SHADER);
            pipeline->VertexShader->InitializeShaderFromFile("data/shaders/shader_common_vs.hlsl");

            pipeline->PixelShader = new RSRender_Shader(RSShaderType::RS_PIXEL_SHADER);
            pipeline->PixelShader->InitializeShaderFromFile("data/shaders/shader_common_ps.hlsl");
        }

        DirectX::XMMATRIX worldMatrix;
        worldMatrix = DirectX::XMMatrixScaling(Size.X, Size.Y, Size.Z);
        worldMatrix *= DirectX::XMMatrixRotationX(DirectX::XMConvertToRadians(Rotation.X));
        worldMatrix *= DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(Rotation.Y));
        worldMatrix *= DirectX::XMMatrixRotationZ(DirectX::XMConvertToRadians(Rotation.Z));
        worldMatrix *= DirectX::XMMatrixTranslation(Position.X, Position.Y, Position.Z);

        pipeline->objectVSConst.world = DirectX::XMMatrixTranspose(worldMatrix);
        pipeline->objectPSConst.isTextured = pipeline->Texture.DrawTexture;

        g_RSRender->l_DeviceContext->UpdateSubresource(pipeline->pixelConst->mpGPUData, 0, NULL, &pipeline->objectPSConst, 0, 0);
        g_RSRender->l_DeviceContext->UpdateSubresource(pipeline->ObjectConstant->mpGPUData, 0, NULL, &pipeline->objectVSConst, 0, 0);

        pipeline->alpha = Opacity;

        pipeline->Draw();

        renderChildren();
    }

} // namespace RS

