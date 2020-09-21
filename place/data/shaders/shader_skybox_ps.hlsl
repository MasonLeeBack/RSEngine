struct VS_OUTPUT
{
    float4 Pos : SV_POSITION;
    float3 normal : NORMAL;
	float2 TexCoord : TEXCOORD;
};

Texture2D tex;
SamplerState samp;

float4 PS(VS_OUTPUT input) : SV_TARGET
{
    input.normal = normalize(input.normal);
    
    float4 diffuse = tex.Sample(samp, input.TexCoord);

    return diffuse;
}