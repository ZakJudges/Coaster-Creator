// Colour pixel/fragment shader
cbuffer ColourBuffer : register(b0)
{
	float4 colour;	
	float4 light_diffuse;
	float4 light_ambient;
	float4 light_direction;
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
	//float4 colour = float4(input.normal, 0.0f);

	float4 result = colour * light_ambient;
	float3 direction = float3(-light_direction.x, -light_direction.y, -light_direction.z);
	float light_intensity;

	//	Calculate the amount of light on this pixel.
	light_intensity = saturate(dot(input.normal, direction));

	if (light_intensity > 0.0f)
	{
		result += (light_diffuse * light_intensity);

		result = saturate(result);
	}

	
	
	return colour * result;
}