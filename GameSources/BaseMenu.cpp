/*!
@file BaseMenu.cpp
@brief メニューの制御クラスの実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void BaseMenu::OnUpdate() {
		auto& app = App::GetApp();
		auto delta = app->GetElapsedTime();
		//コントローラの取得
		const auto& pad = app->GetInputDevice().GetControlerVec()[0];
		bool positive = false;	//+方向
		bool negative = false;	//-方向
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

		if (negative) {
			m_nowMenuNum--;
			m_audio->Start(L"CursorSE", 0, 0.1f);
		}
		if (positive) {
			m_nowMenuNum++;
			m_audio->Start(L"CursorSE", 0, 0.1f);
		}

		if (m_nowMenuNum < 0) {
			m_nowMenuNum = m_menuNum;
		}
		if (m_nowMenuNum > m_menuNum) {
			m_nowMenuNum = 0;
		}

		auto element = m_menuElement[m_nowMenuNum];
		auto transComp = m_cursor.lock()->GetComponent<Transform>();
		auto amount = m_cursorSp * delta;
		auto pos = Lerp::CalculateLerp(transComp->GetPosition(), (Vec3)element.pos, 0.0f, 1.0f, amount, Lerp::rate::EaseOut);
		transComp->SetPosition(pos);


		if (pad.wPressedButtons & XINPUT_GAMEPAD_A && !m_bChange) {
			OnPushButton(element);
			m_audio->Start(L"DecisionSE", 0, 0.1f);
		}

		if (m_bChange) {
			if (m_delta > m_delayTime) {
				BeforeReset();
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
	void BaseMenu::OnPushButton(MenuElement element) {
		OnPushButton(element.sendMsg);
	}


	void BaseMenu::SendEvent(wstring mes) {
		//メッセージを送る
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
