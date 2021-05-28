/*!
@file VSPCTTrickArt.hlsl
@brief トリックアートの見た目を決めるシェーダー
*/

#include "INCTrickArt.hlsli"

PSPCTInput main(VSPCTInput input)
{
	PSPCTInput result;
	//頂点の位置を変換
	float4 pos = float4(input.position.xyz, 1.0f);
	//ワールド変換
	pos = mul(pos, World);
	//ビュー変換
	pos = mul(pos, View);
	//射影変換
	pos = mul(pos, Projection);
	//ピクセルシェーダに渡す変数に設定
	result.position = pos;
	result.color = input.color;
	//テクスチャUV
	result.tex = input.tex;
	return result;
}