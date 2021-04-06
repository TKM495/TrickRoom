/*!
@file BaseMenu.cpp
@brief ���j���[�̐���N���X�̎���
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	//���j���[�Z�b�g�A�b�v
	void BaseMenu::SetUpMenu() {
		//-1�Ȃ͔̂z��ɍ��킹�邽��
		m_menuNum = (int)m_menuElement.size() - 1;

		auto& stage = GetStage();
		for (auto& element : m_menuElement) {
			auto str = stage->AddGameObject<StringSprite2>(element.name);
			str->GetComponent<Transform>()->SetPosition((Vec3)element.pos);
			m_spriteMenu.push_back(str);
		}

		m_cursor = GetStage()->AddGameObject<Cursor>();
	}

	void BaseMenu::OnUpdate() {
		auto& app = App::GetApp();
		auto delta = app->GetElapsedTime();
		//�R���g���[���̎擾
		const auto& pad = app->GetInputDevice().GetControlerVec()[0];
		bool positive = false;	//+����
		bool negative = false;	//-����
		switch (m_dir)
		{
		case MenuDirection::Vertical:
			positive = pad.wPressedButtons & XINPUT_GAMEPAD_DPAD_DOWN;
			negative = pad.wPressedButtons & XINPUT_GAMEPAD_DPAD_UP;
			break;
		case MenuDirection::Horizontal:
			positive = pad.wPressedButtons & XINPUT_GAMEPAD_DPAD_RIGHT;
			negative = pad.wPressedButtons & XINPUT_GAMEPAD_DPAD_LEFT;
			break;
		}

		if (negative &&	m_nowMenuNum > 0) {
			m_nowMenuNum--;
		}
		if (positive &&	m_nowMenuNum < m_menuNum) {
			m_nowMenuNum++;
		}

		auto element = m_menuElement[m_nowMenuNum];

		auto transComp = m_cursor.lock()->GetComponent<Transform>();
		transComp->SetPosition((Vec3)element.pos);


		if (pad.wPressedButtons & XINPUT_GAMEPAD_A && !m_bChange) {
			OnPushButton(element.sendMsg);
		}

		if (m_bChange) {
			if (m_delta > m_delayTime) {
				Reset();
				SendEvent(element.sendMsg);
			}
			m_delta += delta;
		}
	}

	void BaseMenu::OnPushButton() {
		m_bChange = true;
	}

	void BaseMenu::OnPushButton(wstring mes) {
		OnPushButton();
	}

	void BaseMenu::SendEvent(wstring mes) {
		//���b�Z�[�W�𑗂�
		PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), mes);
	}

	void BaseMenu::Reset() {
		m_bChange = false;
		m_delta = 0.0f;
		m_nowMenuNum = 0;
	}

	void BaseMenu::SetDrawMenu(bool flg) {
		for (auto& menu : m_spriteMenu) {
			menu->SetDrawActive(flg);
		}
		m_cursor.lock()->SetDrawActive(flg);
	}
}
//end basecross
