/*!
@file TitleMenu.cpp
@brief タイトルのメニュー管理クラスの実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void TitleMenu::OnCreate() {
		MenuElement titleMenu[]{
			{Vec2(0.0f,-150.0f),L"GameStart",L"ToSelectStage"},
			{Vec2(0.0f,-250.0f),L"Exit",L"ToExit"},
		};

		for (auto element : titleMenu) {
			PushBackElement(element);
		}
		SetUpMenu();
	}

	void TitleMenu::OnPushButton() {
		auto fade = GetStage()->GetSharedGameObject<Fade>(L"Fade");
		SetDelayTime(fade->GetFadeTime());
		fade->FadeOut();
		BaseMenu::OnPushButton();
	}
}
//end basecross
