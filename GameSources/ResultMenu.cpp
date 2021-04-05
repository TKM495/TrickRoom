/*!
@file ResultMenu.cpp
@brief リザルトのメニュー管理クラスの実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void ResultMenu::OnCreate() {
		MenuElement elements[]{
			{Vec2(-400.0f,-300.0f),L"Retry",L"ToGameStage"},
			{Vec2(0.0f,-300.0f),L"StageSelect",L"ToSelectStage"},
			{Vec2(400.0f,-300.0f),L"Exit",L"ToExit"}
		};

		for (auto element : elements) {
			m_menuElement.push_back(element);
		}
		SetUpMenu();
	}

	void ResultMenu::OnPushButton() {
		auto fade = GetStage()->GetSharedGameObject<Fade>(L"Fade");
		m_delayTime = fade->GetFadeTime();
		fade->FadeOut();
		BaseMenu::OnPushButton();
	}
}
//end basecross
