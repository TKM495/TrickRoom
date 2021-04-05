/*!
@file StartCountdown.cpp
@brief �X�^�[�g���̃J�E���g�_�E�����o����
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void StartCountdown::OnCreate() {
		const auto& stage = GetStage();
		m_strObj = stage->AddGameObject<StringSprite2>(L"Start");
		m_strObj->SetDrawActive(false);
		for (int i = 0; i < 3; i++) {
			m_numObjs[i] = stage->AddGameObject<Numbers>(i + 1);
			m_numObjs[i]->SetDrawActive(false);
		}
		m_beforeValue = (int)m_delta;
	}

	void StartCountdown::OnUpdate() {
		auto delta = App::GetApp()->GetElapsedTime();
		//�����̎�
		if (m_delta > 1.0f) {
			auto num = (int)m_delta;
			if (m_beforeValue != num) {
				auto obj = GetStage()->AddGameObject<Numbers>(num);
				obj->GetFadeComp()->FadeIn();
				obj->Deactive(0.5f);
			}
		}
		else {

		}
		m_beforeValue = (int)m_delta;
		m_delta += -delta;
	}
}
//end basecross
