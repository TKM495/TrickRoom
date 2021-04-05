/*!
@file Player.cpp
@brief ÉSÅ[ÉãÇ‹Ç≈ÇÃãóó£ÇÃUIé¿ëÃ
*/

#include "stdafx.h"
#include "Project.h"
#include "UI_Goalgauge.h"

namespace basecross
{
	void UI_Goalgauge::OnCreate()
	{
		float x = 200.0f;
		float y = 200.0f;

		Col4 color(1.0f, 1.0f, 1.0f, 1.0f);
		std::vector<VertexPositionColorTexture> vertices = {
			{Vec3(-x,  y, 0.0f), color, Vec2(0.0f, 0.0f)},
			{Vec3( x,  y, 0.0f), color, Vec2(1.0f, 0.0f)},
			{Vec3(-x, -y, 0.0f), color, Vec2(0.0f, 1.0f)},
			{Vec3( x, -y, 0.0f), color, Vec2(1.0f, 1.0f)}
		};
		std::vector<uint16_t> indices = {
			0, 1, 2,
			2, 1, 3
		};

		auto drawComp = AddComponent<PCTSpriteDraw>(vertices, indices);
		drawComp->SetTextureResource(L"gauge");

		SetAlphaActive(true);

		auto transComp = GetComponent<Transform>();
		Vec3 pos(0.0f, 350.0f, 0.0f);
		transComp->SetPosition(pos);
	}

	void UI_Goalgauge::OnUpdate()
	{}
}