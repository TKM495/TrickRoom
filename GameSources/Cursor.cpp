/*!
@file Cursor.cpp
@brief メニュー用のカーソルクラスの実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void Cursor::OnCreate() {
		//色のデータ(R,G,B,A)
		Col4 color(1.0f, 1.0f, 1.0f, 1.0f);
		//頂点のデータ (番号は左上から右下まで)
		vector<VertexPositionColorTexture> vertices = {
			{Vec3(-300.0f, +50.0f,0.0f),color,Vec2(0.0f,0.0f)}, //0
			{Vec3(+300.0f, +50.0f,0.0f),color,Vec2(1.0f,0.0f)}, //1

			{Vec3(-300.0f, -50.0f,0.0f),color,Vec2(0.0f,1.0f)}, //2
			{Vec3(+300.0f, -50.0f,0.0f),color,Vec2(1.0f,1.0f)},  //3
		};
		//頂点インデックス(頂点をつなげる順番)
		std::vector<uint16_t> indices = {
			0, 1, 2, //上の三角形
			2, 1, 3  //下の三角形
		};

		auto drawComp = AddComponent<PCTSpriteDraw>(vertices, indices);

		drawComp->SetSamplerState(SamplerState::AnisotropicWrap); //テクスチャの繰り返し設定(Wrap)
		drawComp->SetDepthStencilState(DepthStencilState::Read);
		drawComp->SetTextureResource(L"VCursor");
		drawComp->SetDiffuse(Col4(1.0f, 1.0f, 1.0f, 0.3f));

		SetAlphaActive(true);
	}

}
//end basecross
