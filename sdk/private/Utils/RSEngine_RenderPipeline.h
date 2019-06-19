/*

RSEngine
Copyright (c) 2019 Mason Lee Back

*/

#ifndef _RSEngine_RenderPipeline_h_
#define _RSEngine_RenderPipeline_h_

#include <Render/RSRender.h>

namespace rs::Utils {

    class RenderPipeline {
    public:
        // INPUT ASSEMBLER BUFFERS
        Render::RSRender_Buffer* vertexBuffer = nullptr;
        Render::RSRender_Buffer* indexBuffer = nullptr;
        unsigned int indexCount;

        // CRITICAL SHADERS
        Render::RSRender_Shader* vertexShader = nullptr;
        Render::RSRender_Shader* pixelShader = nullptr;

        // OPTIONAL SHADERS

        
        // TEXTURING
        Render::RSRender_Texture* textureObject = nullptr;


        // HELPER FUNCTIONS
        void DrawPipeline();
        void DestroyPipeline();

    };

} // namespace rs::Utils

#endif // _RSEngine_RenderPipeline_h_