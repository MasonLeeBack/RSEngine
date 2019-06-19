/*

RSEngine
Copyright (c) 2019 Mason Lee Back

File name: CommonRender_Types.h

*/

#pragma once
#ifndef _CommonRender_Types_h_
#define _CommonRender_Types_h_

namespace rs::Render {

    using RSTexture2D = void*;
    using RSShaderSamplerState = void*;
    using RSShaderResourceView = void*;
    using RSRenderTargetView = void*;
    using RSShader = void*;

    enum RSPrimitiveTopology {
        RS_PRIMITIVE_TOPOLOGY_POINTLIST,
        RS_PRIMITIVE_TOPOLOGY_LINELIST,
        RS_PRIMITIVE_TOPOLOGY_LINESTRIP,
        RS_PRIMITIVE_TOPOLOGY_TRIANGLELIST,
        RS_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP
    };

    enum RSBufferIdentifier {
        RS_UNSET_BUFFER,
        RS_VERTEX_BUFFER,
        RS_INDEX_BUFFER,
        RS_UNK_BUFFER,
        RS_CONSTANT_BUFFER
    };

    struct RSBufferDesc {
        RSBufferIdentifier id;

        unsigned int uByteWidth;

        unsigned int uStride;
        unsigned int uOffset;

    };

    enum RSShaderStage {
        RS_SHADER_STAGE_VS,
        RS_SHADER_STAGE_HS,
        RS_SHADER_STAGE_DS,
        RS_SHADER_STAGE_GS,
        RS_SHADER_STAGE_PS
    };

    struct RSShaderDesc {
        RSShaderStage stage;
        char* shader_data;
        size_t shader_size;
    };

    enum RSImageType {
        RS_IMAGE_R8G8B8A8_UNORM
    };

    struct RSTextureDesc {
        RSImageType imageType;

        int iWidth;
        int iHeight;

        void* data;
        int  iPitch;
        int  iSlicePitch;
    };

} // namespace rs::Render

#endif // _CommonRender_Types_h_
