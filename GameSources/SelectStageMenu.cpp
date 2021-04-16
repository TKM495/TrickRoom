/*!
@file SelectStageMenu.cpp
@brief ステージセレクトのメニュークラスの実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void SelectStageMenu::OnCreate() {
		m_picFramePos.resize(3);
		auto& stage = GetStage();
		for (int i = 0; i < 3; i++) {
			auto str = stage->AddGameObject<PictureFrame>(i);
			m_picFramePos[i] = Vec3(1280.0f * i, 0.0f, 0.0f);
			str->GetComponent<Transform>()->SetPosition(m_picFramePos[i]);
			m_picFrame.push_back(str);

			auto bg = stage->AddGameObject<BGSprite>(L"BGSelectStage");
			bg->GetComponent<Transform>()->SetPosition(m_picFramePos[i]);
			m_bgObj.push_back(bg);
		}

		m_menuNum = m_picFrame.size() - 1;
	}

	void SelectStageMenu::OnUpdate() {
		auto& app = App::GetApp();
		auto delta = app->GetElapsedTime();
		//コントローラの取得
		const auto& pad = app->GetInputDevice().GetControlerVec()[0];

		m_beforeMenuNum = m_nowMenuNum;

		if (pad.wPressedButtons & XINPUT_GAMEPAD_DPAD_LEFT) {
			m_nowMenuNum--;
			m_audio->Start(L"CursorSE", 0, 0.1f);
		}
		if (pad.wPressedButtons & XINPUT_GAMEPAD_DPAD_RIGHT) {
			m_nowMenuNum++;
			m_audio->Start(L"CursorSE", 0, 0.1f);
		}

		if (m_nowMenuNum < 0) {
			m_nowMenuNum = m_menuNum;
		}
		if (m_nowMenuNum > m_menuNum) {
			m_nowMenuNum = 0;
		}

		auto nowPos = m_picFramePos[m_nowMenuNum];

		if (m_beforeMenuNum != m_nowMenuNum) {
			m_nowPos = m_picFramePos[m_beforeMenuNum];
		}

		auto amount = m_cursorSp * delta;
		m_nowPos = Lerp::CalculateLerp(m_nowPos, nowPos, 0.0f, 1.0f, 0.1f, Lerp::rate::Linear);
		for (int i = 0; i < 3; i++) {
			auto transComp = m_picFrame[i]->GetComponent<Transform>();
			auto pos = m_picFramePos[i];
			transComp->SetPosition(pos - m_nowPos);

			auto bg = m_bgObj[i]->GetComponent<Transform>();
			bg->SetPosition(pos - m_nowPos);
		}

		if (pad.wPressedButtons & XINPUT_GAMEPAD_A && !m_bChange) {
			OnPushButton();
			m_mes = L"ToGameStage";
			m_audio->Start(L"DecisionSE", 0, 0.1f);
		}

		if (pad.wPressedButtons & XINPUT_GAMEPAD_B && !m_bChange) {
			OnPushButton();
			m_mes = L"ToTitleStage";
			m_audio->Start(L"CancelSE", 0, 0.1f);
		}

		if (m_bChange) {
			if (m_delta > m_delayTime) {
				app->GetScene<Scene>()->SetStageNum(m_nowMenuNum + 1);
				Reset();
				SendEvent(m_mes);
			}
			m_delta += delta;
		}
	}

	void SelectStageMenu::OnPushButton() {
		auto fade = GetStage()->GetSharedGameObject<Fade>(L"Fade");
		SetDelayTime(fade->GetFadeTime());
		fade->FadeOut();
		m_bChange = true;
	}

	void SelectStageMenu::OnPushButton(wstring mes) {
		OnPushButton();
	}

	void SelectStageMenu::SendEvent(wstring mes) {
		//メッセージを送る
		PostEvent(0.0f, GetThis<ObjectInterface>(), App::GetApp()->GetScene<Scene>(), mes);
	}

	void SelectStageMenu::Reset() {
		m_bChange = false;
		m_delta = 0.0f;
		m_nowMenuNum = 0;
	}
}
//end basecross
