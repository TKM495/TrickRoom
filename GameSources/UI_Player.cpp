/*!
@file UI_Player.cpp
@brief ÉSÅ[ÉãÇ‹Ç≈ÇÃãóó£ÇÃUIé¿ëÃ
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross
{
	void UI_Player::OnCreate()
	{
		m_startPosX = 130.0f;
		m_goalPosX = -130.0f;

		float x = 25.0f;
		float y = 25.0f;

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
		drawComp->SetTextureResource(L"player");

		SetAlphaActive(true);

		auto transComp = GetComponent<Transform>();
		Vec3 pos(m_startPosX, 350.0f, 0.0f);
		transComp->SetPosition(pos);

		auto player = GetStage()->GetSharedGameObject<Player>(L"Player");
		m_startObjPosX = player->GetComponent<Transform>()->GetPosition().x;
		m_goalObjPosX = dynamic_pointer_cast<GameStage>(GetStage())->GetGoalX();
		m_startToGoalDir = m_goalObjPosX - m_startObjPosX;

		auto fade = AddComponent<FadeComponent>();
		fade->SetFadeTime(0.1f);
		fade->SetFadeColor(color);
		SetDrawActive(false);
	}

	void UI_Player::OnUpdate()
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

		auto player = GetStage()->GetSharedGameObject<Player>(L"Player");
		auto playerPos = player->GetComponent<Transform>()->GetPosition();

		auto transComp = GetComponent<Transform>();
		auto pos = transComp->GetPosition();
		pos.x = Lerp::CalculateLerp(m_startPosX, m_goalPosX, m_startObjPosX, m_goalObjPosX, playerPos.x, Lerp::rate::Linear);

		transComp->SetPosition(pos);
	}

	void UI_Player::FadeIn() {
		SetDrawActive(true);
		auto fade = GetComponent<FadeComponent>();
		fade->FadeIn();
	}
}