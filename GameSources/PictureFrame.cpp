/*!
@file PictureFrame.cpp
@brief StageSelectで使うやつ実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void PictureFrame::OnCreate() {
		auto txSize = Utility::GetTextureSize(L"PictureFrame");
		Vec2 size(600.0f, 600.0f);
		Rect2D<float> pos;

		pos.left = size.x / 2.0f;
		pos.right = size.x / 2.0f;
		pos.top = size.y / 2.0f;
		pos.bottom = size.y / 2.0f;

		Vec2 origin(
			m_nowStage * size.x,
			0.0f
		);

		vector<Vec2> uv = {
			Vec2((origin).x / txSize.x, (origin).y / txSize.y),
			Vec2((origin + size).x / txSize.x, (origin).y / txSize.y),
			Vec2((origin).x / txSize.x, (origin + size).y / txSize.y),
			Vec2((origin + size).x / txSize.x, (origin + size).y / txSize.y)
		};

		Col4 color(1.0f);
		//頂点のデータ (番号は左上から右下まで)
		vector<VertexPositionColorTexture> vertices = {
			{Vec3(-pos.left,+pos.top,0.0f),color,uv[0]}, //0
			{Vec3(+pos.right,+pos.top,0.0f),color,uv[1]}, //1

			{Vec3(-pos.left,-pos.bottom,0.0f),color,uv[2]}, //2
			{Vec3(+pos.right,-pos.bottom,0.0f),color,uv[3]},  //3
		};
		//頂点インデックス
		vector<uint16_t> indices = {
			0, 1, 2, //上の三角形
			2, 1, 3 //下の三角形
		};

		auto drawComp = AddComponent<PCTSpriteDraw>(vertices, indices);
		drawComp->SetTextureResource(L"PictureFrame");
		drawComp->SetSamplerState(SamplerState::AnisotropicWrap); //テクスチャの繰り返し設定(Wrap)
		drawComp->SetDepthStencilState(DepthStencilState::Read);

		SetAlphaActive(true); //透明をサポートする&両面描画になる

	}
}
//end basecross
