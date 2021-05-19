#include "INCPNTStaticDraw2.hlsli"

Texture2D<float4> g_texture : register(t0);
Texture2D g_TADrawMapR : register(t1);
Texture2D g_TADrawMapL : register(t2);
SamplerState g_sampler : register(s0);

float4 main(PSPCTInput input) : SV_TARGET
{
	float4 Light = (saturate(input.color) * Diffuse) + Emissive;
	Light.a = Diffuse.a;
	if (Activeflags.x) {
		Light = g_texture.Sample(g_sampler, input.tex) * Light;
	}

	float2 TATexCoordsR;
	TATexCoordsR.x = 0.5f + (input.TASpacePosR.x / input.TASpacePosR.w * 0.5f);
	TATexCoordsR.y = 0.5f - (input.TASpacePosR.y / input.TASpacePosR.w * 0.5f);

	float2 TATexCoordsL;
	TATexCoordsL.x = 0.5f + (input.TASpacePosL.x / input.TASpacePosL.w * 0.5f);
	TATexCoordsL.y = 0.5f - (input.TASpacePosL.y / input.TASpacePosL.w * 0.5f);

	//　テクスチャカラー
	float4 TexColorR = g_TADrawMapR.Sample(g_sampler, TATexCoordsR);
	float4 TexColorL = g_TADrawMapL.Sample(g_sampler, TATexCoordsL);
	float4 TAColor = TexColorR + TexColorL;

	if (TAColor.w > 0) {
		Light = TAColor;
	}
	return Light;
}