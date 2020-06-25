// Colour pixel/fragment shader
cbuffer ColourBuffer : register(b0)
{
	float4 colour;	//no longer needed.
};

struct InputType
{
	float4 position : SV_POSITION;
	float2 tex : TEXCOORD0;
	float3 normal : NORMAL;
};


float4 main(InputType input) : SV_TARGET
{
	//	Line uses normal container as the colour values.
	float4 colour = float4(input.normal, 0.0f);
	
	return colour;
}