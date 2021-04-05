/*!
@file StartCountdown.cpp
@brief スタート時のカウントダウン演出実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void StartCountdown::OnCreate() {
		const auto& stage = GetStage();
		m_objs[0] = stage->AddGameObject<StringSprite2>(L"Start");
		m_objs[0]->SetDrawActive(false);
		for (int i = 1; i < 4; i++) {
			m_objs[i] = stage->AddGameObject<Numbers>(i);
			m_objs[i]->SetDrawActive(false);
		}
		SetUpdateActive(false);
	}

	void StartCountdown::OnUpdate() {
		auto delta = App::GetApp()->GetElapsedTime();
		if (m_delta > 3.0f) {
			//m_objs[3]->;
		}
		else {
			m_objs[3]->SetDrawActive(false);
		}

		if (m_delta > 2.0f && m_delta <= 3.0f) {
			m_objs[2]->SetDrawActive(true);
		}
		else {
			m_objs[2]->SetDrawActive(false);
		}
		if (m_delta > 1.0f && m_delta <= 2.0f) {
			m_objs[1]->SetDrawActive(true);
		}
		else {
			m_objs[1]->SetDrawActive(false);
		}

		if (m_delta > 0.0f && m_delta <= 1.0f) {
			m_objs[0]->SetDrawActive(true);
		}
		else {
			m_objs[0]->SetDrawActive(false);
		}

		m_delta += -delta;
	}
}
//end basecross
