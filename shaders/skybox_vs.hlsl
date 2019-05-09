/*

RSEngine
Copyright (c) 2019 Mason Lee Back

File name: skybox_vs.hlsl

*/

cbuffer ConstBuffer {
    float4x4 WVP;
};

struct VSIn {
    float4 Pos : SV_POSITION;
    float4 Color : COLOR;
    float2 TexCoord : TEXCOORD;
};

struct PSIn {
    float4 Pos : SV_POSITION;
    float4 Color : COLOR;
    float2 TexCoord : TEXCOORD;
};

PSIn main(VSIn vsi) {
    PSIn output;
    output.Pos = mul(vsi.Pos, WVP);
    output.Color = vsi.Color;
    output.TexCoord = vsi.TexCoord;

    return output;
}
