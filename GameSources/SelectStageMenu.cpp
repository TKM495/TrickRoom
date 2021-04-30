/*!
@file SelectStageMenu.cpp
@brief ステージセレクトのメニュークラスの実体
*/

#include "stdafx.h"
#include "Project.h"

namespace basecross {
	void SelectStageMenu::OnCreate() {
		auto& stage = GetStage();
		m_menuItemBasePos = {
			Vec2(-350.0f, 0.0f),
			Vec2(0.0f, 0.0f),
			Vec2(+350.0f, 0.0f)
		};

		m_menuItemPos = {
			m_menuItemBasePos[0],
			m_menuItemBasePos[1],
			m_menuItemBasePos[2],

			m_menuItemBasePos[0] + Vec2(1280.0f,0.0f),
			m_menuItemBasePos[1] + Vec2(1280.0f,0.0f),
			m_menuItemBasePos[2] + Vec2(1280.0f,0.0f),

			m_menuItemBasePos[0] + Vec2(1280.0f,0.0f) * 2.0f,
			m_menuItemBasePos[1] + Vec2(1280.0f,0.0f) * 2.0f,
			m_menuItemBasePos[2] + Vec2(1280.0f,0.0f) * 2.0f,

			Vec2(1280.0f * 3.0f, 0.0f)
		};

		for (int i = 1; i < 11; i++) {
			auto frame = stage->AddGameObject<PictureFrame>();
			frame->SetSize(0.5f);
			frame->SetPos(m_menuItemPos[i - 1]);
			m_picFrame.push_back(frame);

			int place = static_cast<int>(pow(10, 2 - 1));
			Vec2 offset(-30.0f, 0.0f);

			for (int j = 0; j < 2; j++)
			{
				int value = (i / place) % 10; //任意の桁を取り出す
				place /= 10;
				auto number = stage->AddGameObject<Numbers>(value);
				number->SetPos(m_menuItemPos[i - 1] + offset);
				auto numTrans = number->GetComponent<Transform>();
				numTrans->SetParent(frame);
				offset += Vec2(60.0f, 0.0f);
			}
		}
		for (int i = 0; i < 4; i++) {
			m_menuGroupPos.push_back(Vec2(1280.0f * i, 0.0f));
			auto bg = stage->AddGameObject<BGSprite>(L"BGSelectStage" + to_wstring(i + 1));
			bg->GetComponent<Transform>()->SetPosition((Vec3)m_menuGroupPos[i]);
			m_bgObj.push_back(bg);
		}

		m_menuNum = m_picFrame.size() - 1; //vectorは1～なので
		m_cursor = stage->AddGameObject<Cursor>(L"SelectCursor");
		m_cursor.lock()->SetValue(1.0f, 0.5f);
		auto trans = m_cursor.lock()->GetComponent<Transform>();
		trans->SetScale(Vec3(0.5f));
		trans->SetPosition((Vec3)m_menuItemPos[0]);
	}

	void SelectStageMenu::OnUpdate() {
		auto& app = App::GetApp();
		auto delta = app->GetElapsedTime();
		//コントローラの取得
		const auto& pad = app->GetInputDevice().GetControlerVec()[0];

		m_beforeMenuGroupNum = m_nowMenuGroupNum;

		if (pad.wPressedButtons & XINPUT_GAMEPAD_DPAD_LEFT && !m_bChange) {
			m_nowMenuNum--;
			m_audio->Start(L"CursorSE", 0, 0.1f);

		}
		if (pad.wPressedButtons & XINPUT_GAMEPAD_DPAD_RIGHT && !m_bChange) {
			m_nowMenuNum++;
			m_audio->Start(L"CursorSE", 0, 0.1f);
		}

		if (m_nowMenuNum < 0) {
			m_nowMenuNum = 0;
		}
		if (m_nowMenuNum > m_menuNum) {
			m_nowMenuNum = m_menuNum;
		}
		m_nowMenuGroupNum = m_nowMenuNum / 3;

		auto framePos = m_menuItemBasePos[m_nowMenuNum % 3];
		if (m_nowMenuNum == 9) {
			framePos = m_menuItemBasePos[1];
		}
		auto cursorTrans = m_cursor.lock()->GetComponent<Transform>();
		auto amount = m_cursorSp * delta;
		auto pos = Lerp::CalculateLerp(cursorTrans->GetPosition(), (Vec3)framePos, 0.0f, 1.0f, amount, Lerp::rate::Linear);

		cursorTrans->SetPosition(pos);

		m_nowmenuGroupPos = m_menuGroupPos[m_nowMenuGroupNum];

		if (m_beforeMenuGroupNum != m_nowMenuGroupNum) {
			m_beforeMenuGroupPos = m_menuGroupPos[m_beforeMenuGroupNum];
		}

		auto diffPos = (Vec3)Lerp::CalculateLerp(m_beforeMenuGroupPos, m_nowmenuGroupPos, 0.0f, 1.0f, 0.1f, Lerp::rate::Linear);
		for (int i = 0; i < m_bgObj.size(); i++) {
			auto transComp = m_bgObj[i]->GetComponent<Transform>();
			auto pos = (Vec3)m_menuGroupPos[i];
			transComp->SetPosition(pos - diffPos);
		}
		for (int i = 0; i < m_picFrame.size(); i++) {
			auto transComp = m_picFrame[i]->GetComponent<Transform>();
			auto pos = (Vec3)m_menuItemPos[i];
			transComp->SetPosition(pos - diffPos);
		}
		m_beforeMenuGroupPos = diffPos;

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
		auto fade = GetStage()->GetSharedGameObject<SceneTransition>(L"SceneTransition");
		SetDelayTime(fade->GetTransitionTime());
		fade->Play(SceneTransition::TransDir::Out);
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
