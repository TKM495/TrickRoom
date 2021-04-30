/*!
@file TitleMenu.cpp
@brief �^�C�g���̃��j���[�Ǘ��N���X�̎���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void TitleMenu::OnCreate() {
		MenuElement titleMenu[]{
			{Vec2(0.0f,-100.0f),L"GameStart",L"ToSelectStage"},
			{Vec2(0.0f,-200.0f),L"Exit",L"ToExit"},
		};

		for (auto element : titleMenu) {
			PushBackElement(element);
		}
		SetUpMenu();
	}

	void TitleMenu::OnPushButton() {
		auto fade = GetStage()->GetSharedGameObject<SceneTransition>(L"SceneTransition");
		SetDelayTime(fade->GetTransitionTime());
		fade->Play(SceneTransition::TransDir::Out);
		BaseMenu::OnPushButton();
	}
}
//end basecross
