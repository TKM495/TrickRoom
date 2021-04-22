/*!
@file SelectStageMenu.cpp
@brief ステージセレクトのメニュークラスの実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void SelectStageMenu::OnCreate() {
		auto& stage = GetStage();
		vector<Vec2> positions = {
			Vec2(-450.0f, 220.0f),
			Vec2(-225.0f, 120.0f),
			Vec2(0.0f, 180.0f),
			Vec2(225.0f, 120.0f),
			Vec2(450.0f, 220.0f),
			Vec2(-450.0f, -50.0f),
			Vec2(-225.0f, -150.0f),
			Vec2(0.0f, -100.0f),
			Vec2(225.0f, -150.0f),
			Vec2(450.0f, -50.0f)
		};

		for (int i = 1; i < 11; i++) {
			auto frame = stage->AddGameObject<PictureFrame>();
			frame->SetSize(0.4f);
			frame->SetPos(positions[i - 1]);
			m_picFrame.push_back(frame);

			int place = static_cast<int>(pow(10, 2 - 1));
			Vec2 offset(-30.0f, 0.0f);

			for (int j = 0; j < 2; j++)
			{
				int value = (i / place) % 10; //任意の桁を取り出す
				place /= 10;
				auto number = stage->AddGameObject<Numbers>(value);
				number->SetPos(positions[i - 1] + offset);
				offset += Vec2(60.0f, 0.0f);
			}
		}

		m_menuNum = m_picFrame.size() - 1; //vectorは1～なので
		m_cursor = stage->AddGameObject<Cursor>(L"SelectCursor");
		m_cursor.lock()->SetValue(1.0f, 0.5f);
		auto trans = m_cursor.lock()->GetComponent<Transform>();
		trans->SetScale(Vec3(0.4f));
		trans->SetPosition((Vec3)positions[0]);
	}

	void SelectStageMenu::OnUpdate() {
		auto& app = App::GetApp();
		auto delta = app->GetElapsedTime();
		//コントローラの取得
		const auto& pad = app->GetInputDevice().GetControlerVec()[0];

		if (pad.wPressedButtons & XINPUT_GAMEPAD_DPAD_LEFT) {
			m_nowMenuNum--;
			//m_nowMenuNumは配列基準
			if (m_nowMenuNum == 5 - 1) {
				m_nowMenuNum++;
			}
			else {
				m_audio->Start(L"CursorSE", 0, 0.1f);
			}
		}
		if (pad.wPressedButtons & XINPUT_GAMEPAD_DPAD_RIGHT) {
			m_nowMenuNum++;
			if (m_nowMenuNum == 6 - 1) {
				m_nowMenuNum--;
			}
			else {
				m_audio->Start(L"CursorSE", 0, 0.1f);
			}
		}

		if (pad.wPressedButtons & XINPUT_GAMEPAD_DPAD_UP) {
			m_nowMenuNum -= 5;
			if (m_nowMenuNum < 0) {
				m_nowMenuNum += 5;
			}
			else {
				m_audio->Start(L"CursorSE", 0, 0.1f);
			}
		}
		if (pad.wPressedButtons & XINPUT_GAMEPAD_DPAD_DOWN) {
			m_nowMenuNum += 5;
			if (m_nowMenuNum > m_menuNum) {
				m_nowMenuNum -= 5;
			}
			else {
				m_audio->Start(L"CursorSE", 0, 0.1f);
			}
		}

		if (m_nowMenuNum < 0) {
			m_nowMenuNum = 0;
		}
		if (m_nowMenuNum > m_menuNum) {
			m_nowMenuNum = m_menuNum;
		}

		auto framePos = m_picFrame[m_nowMenuNum]->GetPos();
		auto cursorTrans = m_cursor.lock()->GetComponent<Transform>();
		auto amount = m_cursorSp * delta;
		auto pos = Lerp::CalculateLerp(cursorTrans->GetPosition(), (Vec3)framePos, 0.0f, 1.0f, amount, Lerp::rate::Linear);
		cursorTrans->SetPosition(pos);

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
