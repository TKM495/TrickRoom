/*!
@file SelectStageMenu.cpp
@brief �X�e�[�W�Z���N�g�̃��j���[�N���X�̎���
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
			PushBackElement(element);
		}
		SetUpMenu();
	}

	void SelectStageMenu::OnPushButton() {
		auto fade = GetStage()->GetSharedGameObject<Fade>(L"Fade");
		SetDelayTime(fade->GetFadeTime());
		fade->FadeOut();
		BaseMenu::OnPushButton();
	}
}
//end basecross
