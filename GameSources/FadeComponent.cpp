/*!
@file FadeComponent.cpp
@brief フェードコンポーネント実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void FadeComponent::OnUpdate() {
		if (!m_bActive) {
			return;
		}

		auto draw = GetGameObject()->GetDynamicComponent<SpriteBaseDraw>();
		auto delta = App::GetApp()->GetElapsedTime();

		switch (m_dir)
		{
		case Direction::FadeIn:
			m_delta += +delta;
			break;
		case Direction::FadeOut:
			m_delta += -delta;
			break;
		default:
			break;
		}

		if (m_delta >= 0 && m_delta <= m_fadeTime) {
			auto alpha = (m_delta / m_fadeTime);
			m_color.w = alpha;
			draw->SetDiffuse(m_color);
		}
		else
		{
			switch (m_dir)
			{
			case Direction::FadeIn:
				m_color.w = 1.0f;
				break;
			case Direction::FadeOut:
				m_color.w = 0.0f;
				break;
			default:
				break;
			}
			draw->SetDiffuse(m_color);
			m_bActive = false;
			m_delta = 0.0f;
		}
	}

	void FadeComponent::FadeOut() {
		m_delta = m_fadeTime;
		m_dir = Direction::FadeOut;
		m_bActive = true;
	}

	void FadeComponent::FadeIn() {
		m_delta = 0.0f;
		m_dir = Direction::FadeIn;
		m_bActive = true;
	}
}
//end basecross
