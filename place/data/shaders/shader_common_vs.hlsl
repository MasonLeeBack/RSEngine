cbuffer cbPerObject
{
    matrix worldMatrix;
    matrix viewMatrix;
    matrix projectionMatrix;
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
    output.Pos = mul(inPos, worldMatrix);
    output.Pos = mul(output.Pos, viewMatrix);
    output.Pos = mul(output.Pos, projectionMatrix);
    output.normal = mul(normal, worldMatrix);
	output.TexCoord = inTexCoord;

    return output;
}