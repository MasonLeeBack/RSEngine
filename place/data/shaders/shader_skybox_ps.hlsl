struct VS_OUTPUT
{
    float4 Pos : SV_POSITION;
	float2 TexCoord : TEXCOORD;
    float3 normal : NORMAL;
};

Texture2D tex;
SamplerState samp;

float4 PS(VS_OUTPUT input) : SV_TARGET
{
    input.normal = normalize(input.normal);
    
    float4 diffuse = tex.Sample(samp, input.TexCoord);

    return diffuse;
}