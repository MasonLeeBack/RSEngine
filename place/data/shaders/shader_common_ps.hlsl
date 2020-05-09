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

cbuffer cbPerObject
{
    bool isTextured;
    bool padding[15];
}

Texture2D tex;
SamplerState samp;

float4 PS(VS_OUTPUT input) : SV_TARGET
{
    input.normal = normalize(input.normal);
    
    float4 diffuse = float4(.2,.2,.2,1);
    
    if (isTextured) {
        diffuse = tex.Sample(samp, input.TexCoord);
    }
    
    float3 finalColor;

    finalColor = diffuse * light.ambient;
    finalColor += saturate(dot(light.dir, input.normal) * light.diffuse * diffuse);

    return float4(finalColor, diffuse.a);
}