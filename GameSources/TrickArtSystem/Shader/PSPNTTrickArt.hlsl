/*!
@file PSPNTTrickArt.hlsl
@brief トリックアートの見た目を決めるシェーダー
*/
#include "INCTrickArt.hlsli"

Texture2D g_texture : register(t0);
SamplerState g_sampler : register(s0);

float4 main(PSPNTInput input) : SV_TARGET
{
	float3 lightdir = normalize(LightDir.xyz);
	float3 N1 = normalize(input.norm);
	float4 Light = (saturate(dot(N1, -lightdir)) * Diffuse) + Emissive;
	Light += input.specular;
	Light.a = Diffuse.a;
	if (Activeflags.x) {
		Light = g_texture.Sample(g_sampler, input.tex) * Light;
	}
	return Light;
}