cbuffer ParametersBuffer : register(b0)
{
	float4x4 World	: packoffset(c0);
	float4x4 View	: packoffset(c4);
	float4x4 Projection	: packoffset(c8);
	float4 Emissive : packoffset(c12);
	float4 Diffuse : packoffset(c13);
	float4 Specular : packoffset(c14);
	uint4 Activeflags : packoffset(c15);
	float4 LightDir	: packoffset(c16);
	float4 LightPos	: packoffset(c17);
	float4 EyePos	: packoffset(c18);
	float4x4 LightView	: packoffset(c19);
	float4x4 LightProjection	: packoffset(c23);

	float4x4 TALightView:packoffset(c27);
	float4x4 TALightProjection:packoffset(c31);
};

struct VSPNTInput
{
	float4 position : SV_POSITION;
	float3 norm : NORMAL;
	float2 tex : TEXCOORD;
};

struct PSPNTInputShadow
{
	float4 position : SV_Position;
	float3 norm   : NORMAL0;
	float3 lightRay		: NORMAL1;
	float3 lightView : NORMAL2;
	float3 TARay		: NORMAL3;
	float3 TAView : NORMAL4;
	float4 specular : COLOR;
	float2 tex : TEXCOORD0;
	float4 lightSpacePos : POSITION1;
	float4 TASpacePos : POSITION2;
};