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
		m_color = Col4(1.0f, 1.0f, 1.0f, 0.3f);
		drawComp->SetDiffuse(m_color);

		SetAlphaActive(true);
	}

	void Cursor::OnUpdate() {
		auto delta = App::GetApp()->GetElapsedTime();

		auto time = sinf(m_delta);

		auto alpha = Lerp::CalculateLerp(m_min, m_max, -1.0f, 1.0f, time, Lerp::rate::Linear);

		auto drawComp = GetComponent<PCTSpriteDraw>();
		Col4 color = m_color;
		color.w = alpha;
		drawComp->SetDiffuse(color);

		m_delta += delta * m_rate;
		if (m_delta >= XM_2PI) {
			m_delta = 0.0f;
		}
	}
}
//end basecross
