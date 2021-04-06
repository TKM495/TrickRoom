/*!
@file Pause.cpp
@brief ポーズシステム実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void Pause::OnCreate() {
		auto stage = GetStage();
		stage->SetSharedGameObject(L"Pause", GetThis<Pause>());

		m_titleObj = stage->AddGameObject<StringSprite2>(L"Pause");
		m_titleObj.lock()->SetPos(Vec3(0.0f, 200.0f, 0.0f));
		m_menuObj = stage->AddGameObject<PauseMenu>();

		m_titleObj.lock()->SetDrawActive(false);
		m_menuObj.lock()->SetDrawMenu(false);
	}

	void Pause::IsActive(bool flg) {
		m_titleObj.lock()->SetDrawActive(flg);
		m_menuObj.lock()->SetDrawMenu(flg);
	}
}
//end basecross
