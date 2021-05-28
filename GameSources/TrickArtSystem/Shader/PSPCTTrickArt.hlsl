/*!
@file PSPCTTrickArt.hlsl
@brief トリックアートの見た目を決めるシェーダー
*/

#include "INCTrickArt.hlsli"

Texture2D<float4> g_texture : register(t0);
SamplerState g_sampler : register(s0);

float4 main(PSPCTInput input) : SV_TARGET
{
	float4 Light = (saturate(input.color) * Diffuse) + Emissive;
	Light.a = Diffuse.a;
	if (Activeflags.x) {
		Light = g_texture.Sample(g_sampler, input.tex) * Light;
	}
	return Light;
}