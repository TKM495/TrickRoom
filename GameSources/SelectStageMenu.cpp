/*!
@file SelectStageMenu.cpp
@brief ステージセレクトのメニュークラスの実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void SelectStageMenu::OnCreate() {
		MenuElement elements[]{
			{Vec2(0.0f,200.0f),L"GameStart",L"ToGameStage"},
			//{Vec2(0.0f,-300.0f),L"StageSelect",L"ToSelectStage"},
			{Vec2(0.0f,-200.0f),L"Exit",L"ToTitleStage"}
		};

		for (auto element : elements) {
			m_menuElement.push_back(element);
		}
		SetUpMenu();
	}

	void SelectStageMenu::OnPushButton() {
		auto fade = GetStage()->GetSharedGameObject<Fade>(L"Fade");
		m_delayTime = fade->GetFadeTime();
		fade->FadeOut();
		BaseMenu::OnPushButton();
	}
}
//end basecross
