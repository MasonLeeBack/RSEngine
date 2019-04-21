cbuffer cbPerObject
{
    float4x4 WVP;
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
    output.Pos = inPos;
    output.Color = inColor;
	output.TexCoord = inTexCoord;

    return output;
}

float4 PS(VS_OUTPUT input) : SV_TARGET
{
	return input.Color;
}