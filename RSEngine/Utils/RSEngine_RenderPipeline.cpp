/*

RSEngine
Copyright (c) 2019 Mason Lee Back

File name: RSEngine_RenderPipeline.cpp

Abstract:  RenderPipeline helper class for RSEngine

*/

#include <RSEngine.h>

using namespace rs::Render;

namespace rs::Utils {
    void RenderPipeline::DrawPipeline()
    {
        /* Verify Input Assembler (IA) objects exist. */
        if (!vertexBuffer || !indexBuffer)
            return; // Should we do a runtime error?

        /* Set the vertex and index buffer */
        g_Renderer->SetVertexBuffer(vertexBuffer);
        g_Renderer->SetIndexBuffer(indexBuffer);

        /* Set the vertex shader and pixel shader */
        g_Renderer->SetShader(vertexShader);
        g_Renderer->SetShader(pixelShader);

        /* Check texture. See if we're texturing this object. */
        if (textureObject != nullptr) {
            //g_Renderer->SetShaderResource(RS_SHADER_STAGE_PS, textureObject->getShaderResourceView());
            //g_Renderer->SetShaderSampler(RS_SHADER_STAGE_PS, textureObject->getShaderSamplerState());
        }
        else {
            //g_Renderer->SetShaderResource(RS_SHADER_STAGE_PS, nullptr);
            //g_Renderer->SetShaderSampler(RS_SHADER_STAGE_PS, nullptr);
        }


        g_Renderer->DrawIndexed(indexCount, RS_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    }
} // namespace rs::Utils
