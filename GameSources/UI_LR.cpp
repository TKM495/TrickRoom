/*!
@file Character.cpp
@brief キャラクターなど実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void UI_LR::OnCreate() {
		Col4 color(1.0f, 1.0f, 1.0f, 1.0f);
		auto halfSize = 512.0f;

		vertices = {
			{Vec3(-halfSize,    halfSize, 0.0f), color, Vec2(0.0f,0.0f)},
			{Vec3(halfSize,    halfSize, 0.0f), color, Vec2(0.5f,0.0f)},
			{Vec3(-halfSize, -halfSize, 0.0f), color, Vec2(0.0f, 1.0f)},
			{Vec3(halfSize, -halfSize, 0.0f), color, Vec2(0.5f, 1.0f)}
		};
		std::vector<uint16_t> indices = {
			0, 1, 2,
			2, 1, 3
		};
		auto drawComp = AddComponent<PCTSpriteDraw>(vertices, indices);
		drawComp->SetTextureResource(L"LR");

		SetAlphaActive(true);

		Vec3 pos(-500.0f, -320.0f, 0.0f);
		auto transComp = GetComponent<Transform>();
		transComp->SetScale(Vec3(0.2f));
		transComp->SetPosition(pos);
		m_posX = pos.x;

		auto fade = AddComponent<FadeComponent>();
		fade->SetFadeTime(0.1f);
		fade->SetFadeColor(color);
		SetDrawActive(false);
	}

	void UI_LR::OnUpdate() {
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
			return;
			break;
		}

		auto camera = dynamic_pointer_cast<MainCamera>(GetStage()->GetView()->GetTargetCamera());
		if (!camera->GetbLeapFlg()) {
			SetDrawActive(true);
			Vec2 uv(0.0f);
			switch (camera->GetCamState())
			{
			case state::Left:
				uv = Vec2(0.5f, 1.0f);
				break;
			case state::Right:
				uv = Vec2(0.0f, 0.5f);
				break;
			default:
				break;
			}
			vertices[0].textureCoordinate.x = vertices[2].textureCoordinate.x = uv.x;
			vertices[1].textureCoordinate.x = vertices[3].textureCoordinate.x = uv.y;
			GetComponent<PCTSpriteDraw>()->UpdateVertices(vertices);
			auto transComp = GetComponent<Transform>();
			auto pos = transComp->GetPosition();
			pos.x = m_posX;
			transComp->SetPosition(pos);
		}
		else {
			SetDrawActive(false);
			//数字が逆になっているのは出す画像が示すやつが逆であるため
			switch (camera->GetCamState())
			{
			case state::Left:
				m_posX = 500.0f;
				break;
			case state::Right:
				m_posX = -500.0f;
				break;
			default:
				break;
			}
		}
	}

	void UI_LR::FadeIn() {
		SetDrawActive(true);
		auto fade = GetComponent<FadeComponent>();
		fade->FadeIn();
	}
}
//end basecross
