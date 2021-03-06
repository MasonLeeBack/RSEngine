cbuffer rsViewBuffer : register(b0)
{
    matrix viewMatrix;
    matrix projectionMatrix;
};

cbuffer partBuffer : register (b1)
{
    matrix wmtx;
};

struct VS_INPUT
{
    float3 inPos : POSITION;
    float3 normal : NORMAL;
    float2 inTexCoord : TEXCOORD;
};

struct VS_OUTPUT
{
    float4 Pos : SV_POSITION;
    float3 normal : NORMAL;
	float2 TexCoord : TEXCOORD;
};

VS_OUTPUT VS(VS_INPUT input)
{
    VS_OUTPUT output;
    output.Pos = mul(float4(input.inPos, 1), wmtx);
    output.Pos = mul(output.Pos, viewMatrix);
    output.Pos = mul(output.Pos, projectionMatrix);
    output.normal = mul(input.normal, wmtx);
	output.TexCoord = input.inTexCoord;

    return output;
}