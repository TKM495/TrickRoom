/*!
@file TitleMenu.cpp
@brief タイトルのメニュー管理クラスの実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void TitleMenu::OnCreate() {
		MenuElement titleMenu[]{
			{Vec2(0.0f,-100.0f),L"GameStart",L"ToGameStage"},
			{Vec2(0.0f,-200.0f),L"Exit",L"ToExit"},
		};

		for (auto element : titleMenu) {
			m_menuElement.push_back(element);
		}
		SetUpMenu();
	}

	void TitleMenu::OnPushButton() {
		auto fade = GetStage()->GetSharedGameObject<Fade>(L"Fade");
		m_delayTime = fade->GetFadeTime();
		fade->FadeOut();
		BaseMenu::OnPushButton();
	}
}
//end basecross
