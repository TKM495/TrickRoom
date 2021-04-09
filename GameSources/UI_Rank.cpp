/*!
@file UI_Rank.cpp
@brief スコア等のランク実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void UI_Rank::OnCreate() {
		Vec2 origin;
		switch (m_rank)
		{
		case Rank::S:
			origin = Vec2(0.0f, 0.0f);
			break;
		case Rank::A:
			origin = Vec2(m_originalSize.x, 0.0f);
			break;
		case Rank::B:
			origin = Vec2(m_originalSize.x * 2.0f, 0.0f);
			break;
		case Rank::C:
			origin = Vec2(0.0f, m_originalSize.y);
			break;
		}
		auto halfWidth = m_originalSize.x / 2.0f;
		auto halfHeight = m_originalSize.y / 2.0f;
		Col4 color(1.0f, 1.0f, 1.0f, 1.0f);
		std::vector<VertexPositionColorTexture> vertices = {
			{Vec3(-halfWidth, +halfHeight, 0.0f), color, (origin) / 1024.0f},
			{Vec3(+halfWidth, +halfHeight, 0.0f), color, (origin + Vec2(m_originalSize.x,0.0f)) / 1024.0f},
			{Vec3(-halfWidth, -halfHeight, 0.0f), color, (origin + Vec2(0.0f,m_originalSize.y)) / 1024.0f},
			{Vec3(+halfWidth, -halfHeight, 0.0f), color, (origin + m_originalSize) / 1024.0f}
		};
		std::vector<uint16_t> indices = {
			0, 1, 2,
			2, 1, 3
		};
		auto drawComp = AddComponent<PCTSpriteDraw>(vertices, indices);
		drawComp->SetTextureResource(L"Rank");

		SetAlphaActive(true);
	}

	void UI_Rank::SetSize(float size) {
		GetComponent<Transform>()->SetScale(Vec3(size, size, 0.0f));
	}
	void UI_Rank::SetPosition(Vec2 pos) {
		GetComponent<Transform>()->SetPosition((Vec3)pos);
	}

}
//end basecross
