struct VS_OUTPUT
{
    float4 Pos : SV_POSITION;
	float2 TexCoord : TEXCOORD;
    float3 normal : NORMAL;
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


SamplerState sampState;

Texture2D gTexDiffuse;
Texture2D gTexNormal;
Texture2D gTexPosition;

float4 PS(VS_OUTPUT input) : SV_TARGET
{
    input.normal = normalize(input.normal);
    
    float4 diffuse = tex.Sample(sampState, input.TexCoord);
    
    float3 finalColor;

    finalColor = diffuse * light.ambient;
    finalColor += saturate(dot(light.dir, input.normal) * light.diffuse * diffuse);

    return float4(finalColor, diffuse.a);
}