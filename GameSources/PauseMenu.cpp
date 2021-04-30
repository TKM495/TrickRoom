/*!
@file PauseMenu.cpp
@brief ポーズ画面のメニュー管理クラスの実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void PauseMenu::OnCreate() {
		MenuElement PauseMenu[]{
			{Vec2(0.0f,0.0f),L"Continue",L"Continue"},
			{Vec2(0.0f,-100.0f),L"Retry",L"ToGameStage"},
			{Vec2(0.0f,-200.0f),L"StageSelect",L"ToSelectStage"},
		};

		for (auto element : PauseMenu) {
			PushBackElement(element);
		}
		SetUpMenu();
	}

	void PauseMenu::OnPushButton(wstring mes) {
		if (mes != L"Continue") {
			auto fade = GetStage()->GetSharedGameObject<SceneTransition>(L"SceneTransition");
			SetDelayTime(fade->GetTransitionTime());
			fade->Play(SceneTransition::TransDir::Out);
		}
		BaseMenu::OnPushButton();
	}

	void PauseMenu::SendEvent(wstring mes) {
		if (mes == L"Continue") {
			auto stage = dynamic_pointer_cast<GameStage>(GetStage());
			stage->SetState(GameStage::GameState::PLAYING);
			auto pause = stage->GetSharedGameObject<Pause>(L"Pause");
			pause->IsActive(false);
		}
		else {
			BaseMenu::SendEvent(mes);
		}
	}
}
//end basecross
