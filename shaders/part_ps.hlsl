/*

RSEngine
Copyright (c) 2019 Mason Lee Back

File name: part_ps.hlsl

*/

Texture2D Texture;
SamplerState SampleState;

struct PSIn {
    float4 Pos : SV_POSITION;
    float4 Color : COLOR;
    float2 TexCoord : TEXCOORD;
};

float4 main(PSIn input) : SV_TARGET {
    float4 color;

    color = input.Color;

    color *= Texture.Sample(SampleState, input.TexCoord);

    return color;
}
