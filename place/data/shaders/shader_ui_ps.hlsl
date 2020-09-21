struct VS_OUTPUT
{
    float4 Pos : SV_POSITION;
    float3 normal : NORMAL;
	float2 TexCoord : TEXCOORD;
};

struct Light
{
    float3 dir;
    float3 pos;
    float  range;
    float3 att;
    float4 ambient;
    float4 diffuse;
};

cbuffer cbPerFrame
{
    Light light;
};

cbuffer cbPerObject
{
    bool isTextured;
    bool padding[15];
}

Texture2D tex;
SamplerState samp;

float4 PS(VS_OUTPUT input) : SV_TARGET
{   
    float4 diffuse = float4(0.0f,0.0f,0.0f,0.0f);
    
    if (isTextured) {
        diffuse = tex.Sample(samp, input.TexCoord);
    }
    return diffuse;
}