/*!
@file PictureFrame.cpp
@brief StageSelectで使うやつ実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void PictureFrame::OnCreate() {
		Vec2 size = Utility::GetTextureSize(L"PictureFrame");
		Rect2D<float> pos;

		pos.left = (size.x / 2.0f);
		pos.right = (size.x / 2.0f);
		pos.top = (size.y / 2.0f);
		pos.bottom = (size.y / 2.0f);

		Col4 color(1.0f);
		//頂点のデータ (番号は左上から右下まで)
		vector<VertexPositionColorTexture> vertices = {
			{Vec3(-pos.left,+pos.top,0.0f),color,Vec2(0.0f,0.0f)}, //0
			{Vec3(+pos.right,+pos.top,0.0f),color,Vec2(1.0f,0.0f)}, //1

			{Vec3(-pos.left,-pos.bottom,0.0f),color,Vec2(0.0f,1.0f)}, //2
			{Vec3(+pos.right,-pos.bottom,0.0f),color,Vec2(1.0f,1.0f)},  //3
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

	void PictureFrame::SetPos(Vec2 pos) {
		GetComponent<Transform>()->SetPosition((Vec3)pos);
	}
	void PictureFrame::SetSize(float size) {
		GetComponent<Transform>()->SetScale(Vec3(size));
	}

	Vec2 PictureFrame::GetPos() {
		auto pos = GetComponent<Transform>()->GetPosition();
		return Vec2(pos.x, pos.y);
	}
	float PictureFrame::GetSize() {
		auto scale = GetComponent<Transform>()->GetScale();
		return scale.x;
	}

}
//end basecross
