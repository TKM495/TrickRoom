/*!
@file PauseMenu.cpp
@brief �|�[�Y��ʂ̃��j���[�Ǘ��N���X�̎���
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

	void PauseMenu::OnUpdate() {
		BaseMenu::OnUpdate();
		//Start�{�^���ł����j���[���Ƃ����悤�ɂ�����������
		//���j���[�\���̃{�^���������ꂽ���肪�c���Ă���
		//�J�����u�ԕ���̂ŃR�����g�A�E�g����
		//const auto& pad = App::GetApp()->GetInputDevice().GetControlerVec()[0];
		//if (pad.wPressedButtons & XINPUT_GAMEPAD_START && !IsChange()) {
		//	BaseMenu::OnPushButton();
		//	PauseMenu::SendEvent(L"Continue");
		//}
	}

	void PauseMenu::OnPushButton(wstring mes) {
		if (mes != L"Continue") {
			auto fade = GetStage()->GetSharedGameObject<Fade>(L"Fade");
			SetDelayTime(fade->GetFadeTime());
			fade->FadeOut();
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
