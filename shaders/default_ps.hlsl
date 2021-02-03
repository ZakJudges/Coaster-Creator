
Texture2D shaderTexture : register(t0);
SamplerState SampleType : register(s0);

struct InputType
{
	float4 position : SV_POSITION;
	float2 tex : TEXCOORD0;
	float3 normal : NORMAL;
};


float4 main(InputType input) : SV_TARGET
{
	float4 colour = float4(1.0, 0.0, 0.0, 1.0);
	float4  texture_colour = shaderTexture.Sample(SampleType, input.tex);

	return texture_colour;
}