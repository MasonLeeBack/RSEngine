/*

RSEngine
Copyright (c) 2019 Mason Lee Back

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

File name: Skybox.cpp

*/

#include <Classes/Skybox.h>
#include <Utils/RSEngine_GeometryGenerator.h>

using namespace rs::Render;
using namespace rs::Utils;

namespace rs {
    INITIALIZE_INSTANCE_SOURCE(Skybox);

    void Skybox::tick()
    {
        tickChildren();
    }

    void Skybox::render()
    {
        if (pipeline == nullptr) {
            pipeline = new RenderPipeline;

            GeometryGenerator gen;
            MeshData partMesh = gen.GenerateSphere(1.0f, 128, 128);

            RSBufferDesc vertexDesc;
            vertexDesc.id = RS_VERTEX_BUFFER;
            vertexDesc.uStride = sizeof(vertex) * partMesh.vertexMap.size();

            pipeline->vertexBuffer = g_Renderer->CreateBuffer(vertexDesc);
            pipeline->vertexBuffer->SetBuffer(&(partMesh.vertexMap.front()));

            RSBufferDesc indexDesc;
            indexDesc.id = RS_INDEX_BUFFER;
            indexDesc.uStride = sizeof(unsigned int) * partMesh.vertexIndices.size() * 3;

            pipeline->indexBuffer = g_Renderer->CreateBuffer(indexDesc);
            pipeline->indexBuffer->SetBuffer(&(partMesh.vertexIndices.front()));
            pipeline->indexCount = partMesh.vertexIndices.size();

            pipeline->vertexShader = g_Renderer->CreateShaderFromFile(RS_SHADER_STAGE_VS, "data/shaders/part_vs.rsfx");
            pipeline->pixelShader = g_Renderer->CreateShaderFromFile(RS_SHADER_STAGE_PS, "data/shaders/part_ps.rsfx");

            /*D3D11_RASTERIZER_DESC cmdesc;
            ZeroMemory(&cmdesc, sizeof(D3D11_RASTERIZER_DESC));
            cmdesc.FillMode = D3D11_FILL_SOLID;
            cmdesc.CullMode = D3D11_CULL_BACK;
            cmdesc.FrontCounterClockwise = false;

            cmdesc.CullMode = D3D11_CULL_NONE;
            HRESULT hr = pdx_Device->CreateRasterizerState(&cmdesc, &pipeline->RasterizerState);

            D3D11_DEPTH_STENCIL_DESC dssDesc;
            ZeroMemory(&dssDesc, sizeof(D3D11_DEPTH_STENCIL_DESC));
            dssDesc.DepthEnable = true;
            dssDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
            dssDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;

            pdx_Device->CreateDepthStencilState(&dssDesc, &pipeline->DepthStencilState);*/

            // load the texture data and assign the texture file
            int tex_width, tex_height, tex_bpp;
            unsigned char *data = stbi_load(SkyboxTexture.c_str(), &tex_width, &tex_height, &tex_bpp, STBI_rgb_alpha);
            if (data == NULL)
                return;

            RSTextureDesc desc;
            desc.imageType = RS_IMAGE_R8G8B8A8_UNORM;
            desc.data = data;
            desc.iPitch = tex_width * tex_bpp;
            desc.iSlicePitch = 0;

            pipeline->textureObject = g_Renderer->CreateTexture(desc);
        }

        //pipeline->ViewMatrix = DirectX::XMMatrixScaling(1024.0f, 1024.0f, 1024.0f);
        //pipeline->ViewMatrix *= DirectX::XMMatrixTranslation(-512.0f, -512.0f, -512.0f);

        pipeline->DrawPipeline();

        renderChildren();
    }

} // namespace rs
