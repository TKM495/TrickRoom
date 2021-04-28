/*!
@file SceneTransition.cpp
@brief フェードイン、アウト実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void SceneTransition::OnCreate() {
		GetStage()->SetSharedGameObject(L"SceneTransition", GetThis<SceneTransition>());

		auto size = Utility::GetTextureSize(L"Triangle");
		auto halfWidth = size.x / 2.0f;
		auto halfHeight = size.y / 2.0f;

		Col4 color(1.0f);
		std::vector<VertexPositionColorTexture> vertices = {
			{Vec3(-halfWidth,+halfHeight, 0.0f), color,Vec2(0.0f,0.0f)},
			{Vec3(+halfWidth,+halfHeight, 0.0f), color,Vec2(1.0f,0.0f)},
			{Vec3(-halfWidth,-halfHeight, 0.0f), color,Vec2(0.0f,1.0f)},
			{Vec3(+halfWidth,-halfHeight, 0.0f), color,Vec2(1.0f,1.0f)}
		};
		std::vector<uint16_t> indices = {
			0, 1, 2,
			2, 1, 3
		};
		auto drawComp = AddComponent<PCTSpriteDraw>(vertices, indices);
		drawComp->SetDiffuse(Col4(1.0f));
		drawComp->SetTextureResource(L"Triangle");

		SetSize(0.0f);
		SetAlphaActive(true);

		//画面遷移のやつは画面全体に影響するため最も手前に表示する
		SetDrawLayer(10);
	}

	void SceneTransition::OnUpdate() {
		auto pcSprite = GetComponent<PCTSpriteDraw>();
		auto delta = App::GetApp()->GetElapsedTime();
		Lerp::rate rate;
		if (m_key == 1) {
			rate = Lerp::rate::Easein;
		}
		else {
			rate = Lerp::rate::EaseOut;
		}

		switch (m_state)
		{
		case TransState::Active:
			m_delta += delta;
			if (m_delta < m_Time) {
				auto size = Lerp::CalculateLerp(m_start, m_end, 0.0f, m_Time, m_delta, rate);
				SetSize(size);
				SetRotation(m_delta * 540.0f * m_key);
			}
			else
			{
				m_state = TransState::Stop;
				SetSize(m_end);
				m_delta = 0.0f;
			}
			break;
		case TransState::Stop:
			break;
		}
	}

	void SceneTransition::Play(TransDir dir) {
		switch (dir)
		{
		case TransDir::In:
			m_key = -1;
			m_start = m_maxSize;
			m_end = 0.0f;
			break;
		case TransDir::Out:
			m_key = 1;
			m_start = 0.0f;
			m_end = m_maxSize;
			break;
		default:
			//エラー
			break;
		}
		m_delta = 0.0f;
		m_state = TransState::Active;
	}

	void SceneTransition::SetSize(float size) {
		auto transComp = GetComponent<Transform>();
		transComp->SetScale(size, size, 1.0f);
	}
	void SceneTransition::SetRotation(float deg) {
		auto transComp = GetComponent<Transform>();
		transComp->SetRotation(0.0f, 0.0f, XMConvertToRadians(deg));
	}

}
//end basecross
