/*!
@file Fade.cpp
@brief フェードイン、アウト実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void Fade::OnCreate() {
		GetStage()->SetSharedGameObject(L"Fade", GetThis<Fade>());

		auto viewport = GetStage()->GetView()->GetTargetViewport();
		auto halfWidth = viewport.Width / 2.0f;
		auto halfHeight = viewport.Height / 2.0f;

		//ここで白を指定しているのはDiffuseと乗算になるため
		Col4 color(1.0f);
		std::vector<VertexPositionColor> vertices = {
			{Vec3(-halfWidth,+halfHeight, 0.0f), color},
			{Vec3(+halfWidth,+halfHeight, 0.0f), color},
			{Vec3(-halfWidth,-halfHeight, 0.0f), color},
			{Vec3(+halfWidth,-halfHeight, 0.0f), color}
		};
		std::vector<uint16_t> indices = {
			0, 1, 2,
			2, 1, 3
		};
		auto drawComp = AddComponent<PCSpriteDraw>(vertices, indices);
		drawComp->SetDiffuse(Col4(0.0f));
		SetAlphaActive(true);
		SetDrawLayer(5);
	}

	void Fade::OnUpdate() {
		auto pcSprite = GetComponent<PCSpriteDraw>();
		auto delta = App::GetApp()->GetElapsedTime();

		switch (m_state)
		{
		case FadeState::Active:
			m_delta += delta * m_key;
			if (m_delta >= 0) {
				auto alpha = (m_delta / m_fadeTime);
				pcSprite->SetDiffuse(Col4(0.0f, 0.0f, 0.0f, alpha));
			}
			else
			{
				m_state = FadeState::Stop;
				m_delta = 0.0f;
			}
			break;
		case FadeState::Stop:
			break;
		}
	}

	void Fade::FadeIn() {
		m_key = -1;
		m_delta = m_fadeTime;
		m_state = FadeState::Active;
	}

	void Fade::FadeOut() {
		m_key = 1;
		m_delta = 0.0f;
		m_state = FadeState::Active;
	}
}
//end basecross
