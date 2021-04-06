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

		auto fade = AddComponent<FadeComponent>();
		fade->SetFadeTime(0.1f);
		fade->SetFadeColor(color);
		SetDrawActive(false);
	}

	void UI_Goalgauge::OnUpdate()
	{
		auto stage = dynamic_pointer_cast<GameStage>(GetStage());
		switch (stage->GetState())
		{
		case GameStage::GameState::PLAYING:
			if (!bActive) {
				FadeIn();
				bActive = true;
			}
			break;
		default:
			break;
		}
	}

	void UI_Goalgauge::FadeIn() {
		SetDrawActive(true);
		auto fade = GetComponent<FadeComponent>();
		fade->FadeIn();
	}
}