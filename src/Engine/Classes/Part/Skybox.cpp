/*

RSEngine
Copyright (c) 2020 Mason Lee Back

File name: Skybox.cpp

*/

#include <Classes/Skybox.h>
#include <Renderer/RSRender.h>
#include <Renderer/RSGeometryGenerator.h>

namespace rs {
    INITIALIZE_INSTANCE_SOURCE(Skybox);

    void Skybox::render() {

        if (pipeline == nullptr) {
            pipeline = new RSRenderPipeline;

            GeometryGenerator gen;
            MeshData partMesh = gen.GenerateCube();

            pipeline->createBuffersForMesh(partMesh);

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

            //ZeroMemory(&pipeline->objectPSConst, sizeof(psConst_PerObject));

            pipeline->VertexShader = new RSRender_Shader(RSShaderType::RS_VERTEX_SHADER);
            pipeline->VertexShader->InitializeShaderFromFile("data/shaders/shader_skybox_vs.hlsl");

            pipeline->PixelShader = new RSRender_Shader(RSShaderType::RS_PIXEL_SHADER);
            pipeline->PixelShader->InitializeShaderFromFile("data/shaders/shader_skybox_ps.hlsl");

            pipeline->cullState = RSCullState::CullNone;
        }

        DirectX::XMMATRIX worldMatrix;
        worldMatrix = DirectX::XMMatrixScaling(500, 500, 500);

        pipeline->objectVSConst.world = DirectX::XMMatrixTranspose(worldMatrix);
        pipeline->objectPSConst.isTextured = pipeline->Texture.DrawTexture;

        g_RSRender->l_DeviceContext->UpdateSubresource(pipeline->ObjectConstant->mpGPUData, 0, NULL, &pipeline->objectVSConst, 0, 0);
        g_RSRender->l_DeviceContext->UpdateSubresource(pipeline->pixelConst->mpGPUData, 0, NULL, &pipeline->objectPSConst, 0, 0);

        pipeline->Draw();

        renderChildren();
    }

} // namespace RS

