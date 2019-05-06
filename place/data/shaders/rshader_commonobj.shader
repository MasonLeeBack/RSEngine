cbuffer cbPerObject
{
    float4x4 WVP;
    bool texturedObject;
};

struct VS_OUTPUT
{
    float4 Pos : SV_POSITION;
    float4 Color : COLOR;
	float2 TexCoord : TEXCOORD;
};

VS_OUTPUT VS(float4 inPos : POSITION, float4 inColor : COLOR, float2 inTexCoord : TEXCOORD)
{
    VS_OUTPUT output;
    output.Pos = mul(inPos, WVP);
    output.Color = inColor;
	output.TexCoord = inTexCoord;

    return output;
}

Texture2D tex;
SamplerState samp;

float4 PS(VS_OUTPUT input) : SV_TARGET
{
    float4 color;

    color = input.Color;

    return color * tex.Sample(samp, input.TexCoord);
}