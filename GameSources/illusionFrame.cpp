/*!
@file illusionFrame.cpp
@brief 錯視フレームの実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void illusionFrame::SetPosition(Vec2 pos) {
		GetComponent<Transform>()->SetPosition((Vec3)pos);
	}

	void illusionFrame::OnCreate() {
		auto texSize = Utility::GetTextureSize(m_texName);

		Col4 color(1.0f);
		auto halfWidth = texSize.x / 2.0f;
		auto halfHeight = texSize.y / 8.0f; //このテクスチャは3セットなので半分の半分の半分の半分
		vertices = {
			{Vec3(-halfWidth, +halfHeight, 0.0f),color,Vec2(0.0f,0.25f)},  //0
			{Vec3(+halfWidth, +halfHeight, 0.0f),color,Vec2(1.0f,0.25f)},  //1
			{Vec3(-halfWidth, -halfHeight, 0.0f),color,Vec2(0.0f,0.5f)},  //2
			{Vec3(+halfWidth, -halfHeight, 0.0f),color,Vec2(1.0f,0.5f)},  //3
		};
		//頂点インデックス
		vector<uint16_t> indices = {
			0, 1, 2,
			2, 1, 3
		};

		auto drawComp = AddComponent<PCTSpriteDraw>(vertices, indices);
		drawComp->SetTextureResource(m_texName);
		drawComp->SetSamplerState(SamplerState::AnisotropicWrap); //テクスチャの繰り返し設定(Wrap)
		drawComp->SetDepthStencilState(DepthStencilState::Read);

		SetAlphaActive(true); //透明をサポートする&両面描画になる
	}

	void illusionFrame::SetFrameActive(Status stat) {
		vector<Vec2> uv;
		switch (stat)
		{
		case Status::Active:
			uv = {
				Vec2(0.0f,0.0f),
				Vec2(1.0f,0.0f),
				Vec2(0.0f,0.25f),
				Vec2(1.0f,0.25f)
			};
			break;
		case Status::Invalid:
			uv = {
				Vec2(0.0f,0.25f),
				Vec2(1.0f,0.25f),
				Vec2(0.0f,0.5f),
				Vec2(1.0f,0.5f)
			};
			break;
		case Status::Neutral:
			uv = {
				Vec2(0.0f,0.5f),
				Vec2(1.0f,0.5f),
				Vec2(0.0f,0.75f),
				Vec2(1.0f,0.75f)
			};
			break;
		default:
			//エラー
			break;
		}
		for (int i = 0; i < vertices.size(); i++) {
			vertices[i].textureCoordinate = uv[i];
		}
		GetComponent<PCTSpriteDraw>()->UpdateVertices(vertices);
	}
}
//end basecross