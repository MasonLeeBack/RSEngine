cbuffer rsViewBuffer : register(b0)
{
    matrix viewMatrix;
    matrix projectionMatrix;
};

cbuffer partBuffer : register (b1)
{
    matrix wmtx;
};

struct VS_OUTPUT
{
    float4 Pos : SV_POSITION;
	float2 TexCoord : TEXCOORD;
    float3 normal : NORMAL;
};

VS_OUTPUT VS(float4 inPos : POSITION, float2 inTexCoord : TEXCOORD, float3 normal : NORMAL)
{
    VS_OUTPUT output;
    output.Pos = mul(inPos, wmtx);
    output.Pos = mul(output.Pos, viewMatrix);
    output.Pos = mul(output.Pos, projectionMatrix);
    output.normal = mul(normal, wmtx);
	output.TexCoord = inTexCoord;

    return output;
}